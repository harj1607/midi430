/* DriverLib Includes */
#include <src/keyboard.h>
#include <msp430.h>

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>


int main(void)
{
    /* Halting WDT */
    WDTCTL = WDTPW | WDTHOLD;

    /* Configure DCO at 12MHz */
    DCOCTL = 0;
    BCSCTL1 = CALBC1_12MHZ;
    DCOCTL = CALDCO_12MHZ;

    /* Initalize the LED */
    P1OUT = 0;
    P1DIR |= BIT0;

    /* Initialise the keyboard */
    keyboard_init();

    __bis_SR_register(GIE);

    do_keyboard();
}


