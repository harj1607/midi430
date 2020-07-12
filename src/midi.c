#include "midi.h"
#include "queue.h"
#include <msp430.h>


/* Transmit queue */
#define TX_QUEUE_SIZE 32
struct queue_t tx_queue;
uint8_t tx_buffer[TX_QUEUE_SIZE];

/* Transmit queue */
#define RX_QUEUE_SIZE 32
struct queue_t rx_queue;
uint8_t rx_buffer[RX_QUEUE_SIZE];


#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCI0RX_ISR(void)
{
    queue_push_back(&rx_queue, UCA0RXBUF);
}


#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{
    P1OUT |= BIT0;

    if (!queue_empty(&tx_queue)) {
        UCA0TXBUF = queue_pop_front(&tx_queue);
    } else {
        // Nothing else to send
        IE2 &= ~UCA0TXIE;
    }

    P1OUT &= ~BIT0;
}



void midi_init(void)
{
    /* Initialise the UART RX and TX queues */
    queue_init(&tx_queue);
    queue_init(&rx_queue);
    tx_queue.buffer = tx_buffer;
    tx_queue.size = TX_QUEUE_SIZE;
    rx_queue.buffer = rx_buffer;
    rx_queue.size = RX_QUEUE_SIZE;

    /* Selecting P1.1 (RXD) and P1.2 (TXD) in UART mode */
    P1SEL |= BIT1 + BIT2;
    P1SEL2 |= BIT1 + BIT2;
    P1DIR |= BIT2;
    /* At 12MHz, 31250 bps, clockPrescalar=384, firstModReg=0, secondModReg=0, overSampling=1 */
    UCA0CTL0 = 0;
    UCA0CTL1 |= UCSSEL_2;
    UCA0BR0 = 128;
    UCA0BR1 = 1;
    UCA0MCTL = 0;
    UCA0CTL1 &= ~UCSWRST;
    /* Enabling interrupts */
    IE2 |= UCA0RXIE;
}


void midi_send(uint8_t c)
{
    queue_push_back(&tx_queue, c);

    // Trigger UART TX interrupt
    IE2 |= UCA0TXIE;
}


void midi_noteon(uint8_t ch, uint8_t note, uint8_t vel)
{
    midi_send(MIDI_COMMAND_NOTE_ON | ((ch-1) & 0x0F));
    midi_send(note);
    midi_send(vel);
}


void midi_noteoff(uint8_t ch, uint8_t note, uint8_t vel)
{
    midi_send(MIDI_COMMAND_NOTE_OFF | ((ch-1) & 0x0F));
    midi_send(note);
    midi_send(vel);
}


void midi_all_sound_off()
{
    midi_send(MIDI_COMMAND_CHANNEL_MODE);
    midi_send(120);
    midi_send(0);
}


void midi_reset_all_controllers()
{
//    midi_send(MIDI_COMMAND_CHANNEL_MODE);
//    midi_send(121);
//    midi_send(x);
}


void midi_local_control_on()
{
    midi_send(MIDI_COMMAND_CHANNEL_MODE);
    midi_send(122);
    midi_send(127);
}


void midi_local_control_off()
{
    midi_send(MIDI_COMMAND_CHANNEL_MODE);
    midi_send(122);
    midi_send(0);
}


void midi_all_notes_off()
{
    midi_send(MIDI_COMMAND_CHANNEL_MODE);
    midi_send(MIDI_CHANNEL_MODE_ALL_NOTES_OFF);
    midi_send(0);
}


void midi_omni_mode_off()
{
    midi_send(MIDI_COMMAND_CHANNEL_MODE);
    midi_send(MIDI_CHANNEL_MODE_OMNI_MODE_OFF);
    midi_send(0);
}


void midi_omni_mode_on()
{
    midi_send(MIDI_COMMAND_CHANNEL_MODE);
    midi_send(MIDI_CHANNEL_MODE_OMNI_MODE_ON);
    midi_send(0);
}


void midi_mono_mode_on(uint8_t nchannels)
{
    midi_send(MIDI_COMMAND_CHANNEL_MODE);
    midi_send(MIDI_CHANNEL_MODE_MONO_MODE_ON);
    midi_send(nchannels);
}


void midi_poly_mode_on()
{
    midi_send(MIDI_COMMAND_CHANNEL_MODE);
    midi_send(MIDI_CHANNEL_MODE_POLY_MODE_ON);
    midi_send(0);
}
