#include "keyboard.h"
#include "midi.h"

#include <msp430.h>


static uint8_t raw_keys[KEYBOARD_NB_KEYS/8+1];
static uint8_t velocity = MIDI_STANDARD_VELOCITY;
static uint8_t channel = 1;

static key_t keys[KEYBOARD_NB_KEYS];

void keyboard_init(void)
{
    int i;
	midi_init();

	P1SEL |=  BIT5 | BIT6;
	P1SEL2 |= BIT5 | BIT6;
	P2DIR |=  BIT4 | BIT5;
	UCB0CTL0 |= UCCKPL + UCMSB + UCMST + UCSYNC; // 3-pin, 8-bit SPI MASTER
	UCB0CTL1 |= UCSSEL_2; // SMCLK
	UCB0BR0 = 24; // /2
	UCB0BR1 = 0;
	UCB0CTL1 &= ~UCSWRST; // Initialize USCI state machine

    /* Delaying waiting for the module to initialize */
	__delay_cycles(75);

	/* Initialize all keys */
    for (i=0; i<KEYBOARD_NB_KEYS; ++i) {
        key_init(&keys[i], i+KEYBOARD_NOTE_OFFSET);
    }
}


void keyboard_scan(uint8_t *keys, int n)
{
    /* Load keys by toggling PL */
    P2OUT &= ~BIT5;
    __delay_cycles(10);
    P2OUT |= BIT5;

    /* CE = 0 */
    P2OUT &= ~BIT4;

    while(n--)
    {
    	UCB0TXBUF = 0;
    	// ...wait...
    	while(UCB0STAT & UCBUSY);
    	// -->receive
    	keys[n] = ~UCB0RXBUF;
    }

    /* CE = 1 */
    P2OUT |= BIT4;
}


void do_keyboard(void)
{
    int i;
	uint8_t raw_mask;
	uint8_t raw_idx;

	midi_all_notes_off();

	while (1) {

//	    if (!queue_empty(&rx_queue)) {
//	        uint8_t c = queue_pop_front(&rx_queue);
//
//	        if (c & 0x80) {
//
//	        }
//	    }

	    keyboard_scan(raw_keys, KEYBOARD_NB_KEYS/8+1);

	    raw_idx = 0;
	    raw_mask = 0x01;

	    for (i=0; i<KEYBOARD_NB_KEYS; i++) {

	        key_t* key = &keys[i];

	        bool pressed = raw_keys[raw_idx] & raw_mask;

	        if (key_update(key, pressed)) {
                if (key->state == KEY_STATE_ON) {
	                // Note on
	                midi_noteon(channel, key->note, velocity);
	            } else {
	                // Note off
	                midi_noteoff(channel, key->note, velocity);
                }
			}

	        if (raw_mask == 0x80) {
	            raw_mask = 0x01;
	            raw_idx++;
	        } else {
	            raw_mask = raw_mask << 1;
	        }
	    }
	}
}


void key_init(key_t* key, uint8_t note)
{
    key->count = 0;
    key->state = KEY_STATE_OFF;
    key->note = note;
}


bool key_update(key_t* key, bool input)
{
    switch (key->state) {
    case KEY_STATE_OFF:
        if (input == true) {
            key->count++;
            if (key->count >= KEY_DELAY_ON) {
                key->count = 0;
                key->state = KEY_STATE_ON;
            }
            return true;
        } else {
            key->count = 0;
        }
        break;

    case KEY_STATE_ON:
        if (input == false) {
            key->count++;
            if (key->count >= KEY_DELAY_OFF) {
                key->count = 0;
                key->state = KEY_STATE_OFF;
                return true;
            }
        } else {
            key->count = 0;
        }
        break;
    }

    return false;
}

