#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>

/// Number of keys
#define KEYBOARD_NB_KEYS       44
/// Note of first key
#define KEYBOARD_NOTE_OFFSET   41 // F2


void keyboard_init(void);
void keyboard_scan(uint8_t *keys, int n);
void do_keyboard(void);

#endif
