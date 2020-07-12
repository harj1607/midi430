#include "keyboard.h"
#include "midi.h"

#include <msp430.h>


static uint8_t keys[KEYBOARD_NB_KEYS/8+1];
static uint8_t old_keys[KEYBOARD_NB_KEYS/8+1];
static uint8_t velocity = MIDI_STANDARD_VELOCITY;
static uint8_t channel = 1;


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

    /* Reset old keys */
    for (i=0; i<(KEYBOARD_NB_KEYS/8+1); i++)
    	old_keys[i] = 0x00;

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
	uint8_t mask;
	uint8_t idx;
	uint8_t bit;
	uint8_t change;
	uint8_t note;

	midi_all_notes_off();

	while (1) {

//	    if (!queue_empty(&rx_queue)) {
//	        uint8_t c = queue_pop_front(&rx_queue);
//
//	        if (c & 0x80) {
//
//	        }
//	    }

	    keyboard_scan(keys, KEYBOARD_NB_KEYS/8+1);

	    idx = 0;

	    for (i=0; i<(KEYBOARD_NB_KEYS/8+1); i++) {

	        change = old_keys[idx] ^ keys[idx];

	        if (change) {
	            mask = 0x01;

	            for (bit=0; bit<8; bit++) {
	                if (change & mask) {
	                    note = i*8+bit+KEYBOARD_NOTE_OFFSET;

	                    if (keys[idx] & mask) {
	                        // Note on
	                        midi_noteon(channel, note, velocity);
	                    } else {
	                        // Note off
	                        midi_noteoff(channel, note, velocity);
	                    }
	                }

	                mask = mask << 1;
	            }
			}

	        old_keys[idx] = keys[idx];
	        idx++;
	    }
	}
}


