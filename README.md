# midi430

This is a MIDI keyboard project for the MSP430G2553.

# Construction

The keyboard is an old Hammond Romance keyboard. 

## Debounce circuit

The keys are normally open contacts. Each key is fed to a debounce circuit made of a 10K pull-up resistor to +3.3V and a 0.1uF capacitor in parallel.

## Serializer

The keys are connected to a bunch (6) of 74HC165 in daisy chain and connected to the SPI MISO pin of the MSP430. Each 74HC165 can read up to 8 keys.

Pin 1 (PL/LD)    ->  To 
Pin 2 (CLK)      ->  SCLK
Pin 3 (E)        ->  Key debounce circuit
Pin 4 (F)        ->  Key debounce circuit
Pin 5 (G)        ->  Key debounce circuit
Pin 6 (H)        ->  Key debounce circuit
Pin 7 (\Q\H)     ->  N.C.
Pin 8 (GND)      ->  GND
Pin 9 (QH)       ->  To Pin 10 (SER) of other 74HC165 or to MISO
Pin 10 (SER)     ->  From Pin 9 of other 74HC165 or left unconnected
Pin 11 (A)       ->  Key debounce circuit
Pin 12 (B)       ->  Key debounce circuit
Pin 13 (C)       ->  Key debounce circuit
Pin 14 (D)       ->  Key debounce circuit
Pin 15 (CLK INH) ->  To 
Pin 16 (VCC)     ->  +3.3V

## MIDI transmitter circuit

The MIDI Output is made with a 7404 connected to the UART TX pin. Two inverters are used as a buffer and fed to a 220 ohms resistor and to the MIDI Out port. The MIDI loop is powered by a +5V voltage fed through another 220 ohms resistor.

UART TX ---|>o--|>o--/\/\/----- To MIDI Pin 5
    +5V ---------/\/\/--------- To MIDI Pin 4

