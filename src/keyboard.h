#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <stdint.h>
#include <stdbool.h>

/// Number of keys
#define KEYBOARD_NB_KEYS       44
/// Note of first key
#define KEYBOARD_NOTE_OFFSET   41 // F2

#define KEY_STATE_OFF               0
#define KEY_STATE_ON                1

// Debounce threshold
#define KEY_DELAY_ON                1
#define KEY_DELAY_OFF               10

// Key structure
typedef struct {
    uint16_t count;
    uint8_t state;
    uint8_t note;       // MIDI Note
} key_t;

void key_init(key_t* key, uint8_t note);
bool key_update(key_t* key, bool input);

void keyboard_init(void);
void keyboard_scan(uint8_t *keys, int n);
void do_keyboard(void);

#endif
