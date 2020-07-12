#ifndef MIDI_H_
#define MIDI_H_

#include <stdint.h>


#define MIDI_COMMAND_NOTE_OFF                0x80 /* Note Off event */
#define MIDI_COMMAND_NOTE_ON                 0x90 /* Note On event */
#define MIDI_COMMAND_POLYPHONIC_KEY_PRESSURE 0xA0 /* Polyphonic Key Pressure (Aftertouch) */
#define MIDI_COMMAND_CONTROL_CHANGE          0xB0 /* Control Change */
#define MIDI_COMMAND_PROGRAM_CHANGE          0xC0 /* Program Change */
#define MIDI_COMMAND_CHANNEL_PRESSURE        0xD0 /* Channel Pressure (Aftertouch) */
#define MIDI_COMMAND_PITCH_BEND_CHANGE       0xE0 /* Pitch Bend Change */
#define MIDI_COMMAND_CHANNEL_MODE            0xA0 /* Channel Mode Messages */

// Control Changes and Mode Changes
#define MIDI_CONTROL_BANK_SELECT                  0x00
#define MIDI_CONTROL_MODULATION_WHEEL             0x01
#define MIDI_CONTROL_BREATH_CONTROLLER            0x02
#define MIDI_CONTROL_UNDEFINED_03                 0x03
#define MIDI_CONTROL_FOOT_CONTROLLER              0x04
#define MIDI_CONTROL_PORTAMENTO_TIME              0x05
#define MIDI_CONTROL_DATA_ENTRY_MSB               0x06
#define MIDI_CONTROL_CHANGE_VOLUME                0x07
#define MIDI_CONTROL_BALANCE                      0x08
#define MIDI_CONTROL_UNDEFINED_09                 0x09
#define MIDI_CONTROL_PAN                          0x0A
#define MIDI_CONTROL_EXPRESSION_CONTROLLER        0x0B
#define MIDI_EFFECT_CONTROL_1                     0x0C
#define MIDI_EFFECT_CONTROL_2                     0x0D
#define MIDI_CONTROL_UNDEFINED_0E                 0x0E
#define MIDI_CONTROL_UNDEFINED_0F                 0x0F
#define MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_1 0x10
#define MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_2 0x11
#define MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_3 0x12
#define MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_4 0x13
#define MIDI_CONTROL_UNDEFINED_14                 0x14
#define MIDI_CONTROL_UNDEFINED_15                 0x15
#define MIDI_CONTROL_UNDEFINED_16                 0x16
#define MIDI_CONTROL_UNDEFINED_17                 0x17
#define MIDI_CONTROL_UNDEFINED_18                 0x18
#define MIDI_CONTROL_UNDEFINED_19                 0x19
#define MIDI_CONTROL_UNDEFINED_1A                 0x1A
#define MIDI_CONTROL_UNDEFINED_1B                 0x1B
#define MIDI_CONTROL_UNDEFINED_1C                 0x1C
#define MIDI_CONTROL_UNDEFINED_1D                 0x1D
#define MIDI_CONTROL_UNDEFINED_1E                 0x1E
#define MIDI_CONTROL_UNDEFINED_1F                 0x1F
#define MIDI_CONTROL_LSB_FOR_CONTROL_0            0x20
#define MIDI_CONTROL_LSB_FOR_CONTROL_1            0x21
#define MIDI_CONTROL_LSB_FOR_CONTROL_2            0x22
#define MIDI_CONTROL_LSB_FOR_CONTROL_3            0x23
#define MIDI_CONTROL_LSB_FOR_CONTROL_4            0x24
#define MIDI_CONTROL_LSB_FOR_CONTROL_5            0x25
#define MIDI_CONTROL_LSB_FOR_CONTROL_6            0x26
#define MIDI_CONTROL_LSB_FOR_CONTROL_7            0x27
#define MIDI_CONTROL_LSB_FOR_CONTROL_8            0x28
#define MIDI_CONTROL_LSB_FOR_CONTROL_9            0x29
#define MIDI_CONTROL_LSB_FOR_CONTROL_10           0x2A
#define MIDI_CONTROL_LSB_FOR_CONTROL_11           0x2B
#define MIDI_CONTROL_LSB_FOR_CONTROL_12           0x2C
#define MIDI_CONTROL_LSB_FOR_CONTROL_13           0x2D
#define MIDI_CONTROL_LSB_FOR_CONTROL_14           0x2E
#define MIDI_CONTROL_LSB_FOR_CONTROL_15           0x2F
#define MIDI_CONTROL_LSB_FOR_CONTROL_16           0x30
#define MIDI_CONTROL_LSB_FOR_CONTROL_17           0x31
#define MIDI_CONTROL_LSB_FOR_CONTROL_18           0x32
#define MIDI_CONTROL_LSB_FOR_CONTROL_19           0x33
#define MIDI_CONTROL_LSB_FOR_CONTROL_20           0x34
#define MIDI_CONTROL_LSB_FOR_CONTROL_21           0x35
#define MIDI_CONTROL_LSB_FOR_CONTROL_22           0x36
#define MIDI_CONTROL_LSB_FOR_CONTROL_23           0x37
#define MIDI_CONTROL_LSB_FOR_CONTROL_24           0x38
#define MIDI_CONTROL_LSB_FOR_CONTROL_25           0x39
#define MIDI_CONTROL_LSB_FOR_CONTROL_26           0x3A
#define MIDI_CONTROL_LSB_FOR_CONTROL_27           0x3B
#define MIDI_CONTROL_LSB_FOR_CONTROL_28           0x3C
#define MIDI_CONTROL_LSB_FOR_CONTROL_29           0x3D
#define MIDI_CONTROL_LSB_FOR_CONTROL_30           0x3E
#define MIDI_CONTROL_LSB_FOR_CONTROL_31           0x3F
#define MIDI_CONTROL_DAMPER_PEDAL_ON_OFF          0x40
#define MIDI_CONTROL_PORTAMENTO_ON_OFF            0x41
#define MIDI_CONTROL_SOSTENUTO_ON_OFF             0x42
#define MIDI_CONTROL_SOFT_PEDAL_ON_OFF            0x43
#define MIDI_CONTROL_LEGATO_FOOTSWITCH            0x44
#define MIDI_CONTROL_HOLD_2                          0x45
#define MIDI_CONTROL_SOUND_CONTROLLER_1              0x46
#define MIDI_CONTROL_SOUND_CONTROLLER_2              0x47
#define MIDI_CONTROL_SOUND_CONTROLLER_3              0x48
#define MIDI_CONTROL_SOUND_CONTROLLER_4              0x49
#define MIDI_CONTROL_SOUND_CONTROLLER_5              0x4A
#define MIDI_CONTROL_SOUND_CONTROLLER_6              0x4B
#define MIDI_CONTROL_SOUND_CONTROLLER_7              0x4C
#define MIDI_CONTROL_SOUND_CONTROLLER_8              0x4D
#define MIDI_CONTROL_SOUND_CONTROLLER_9              0x4E
#define MIDI_CONTROL_SOUND_CONTROLLER_10             0x4F
#define MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_5    0x50
#define MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_6    0x51
#define MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_7    0x52
#define MIDI_CONTROL_GENERAL_PURPOSE_CONTROLLER_8    0x53
#define MIDI_CONTROL_PORTAMENTO_CONTROL              0x54
#define MIDI_CONTROL_UNDEFINED_55                    0x55
#define MIDI_CONTROL_UNDEFINED_56                    0x56
#define MIDI_CONTROL_UNDEFINED_57                    0x57
#define MIDI_CONTROL_HIGH_RESOLUTION_VELOCITY_PREFIX 0x58
#define MIDI_CONTROL_UNDEFINED_59                    0x59
#define MIDI_CONTROL_UNDEFINED_5A                    0x5A
#define MIDI_CONTROL_EFFECTS_1_DEPTH                 0x5B
#define MIDI_CONTROL_EFFECTS_2_DEPTH                 0x5C
#define MIDI_CONTROL_EFFECTS_3_DEPTH                 0x5D
#define MIDI_CONTROL_EFFECTS_4_DEPTH                 0x5E
#define MIDI_CONTROL_EFFECTS_5_DEPTH                 0x5F
#define MIDI_CONTROL_DATA_INCREMENT                  0x60
#define MIDI_CONTROL_DATA_DECREMENT                  0x61
#define MIDI_CONTROL_NRPN_LSB                        0x62
#define MIDI_CONTROL_NRPN_MSB                        0x63
#define MIDI_CONTROL_RPN_LSB                         0x64
#define MIDI_CONTROL_RPN_MSB                         0x65
#define MIDI_CONTROL_UNDEFINED_66                    0x66
#define MIDI_CONTROL_UNDEFINED_67                    0x67
#define MIDI_CONTROL_UNDEFINED_68                    0x68
#define MIDI_CONTROL_UNDEFINED_69                    0x69
#define MIDI_CONTROL_UNDEFINED_6A                    0x6A
#define MIDI_CONTROL_UNDEFINED_6B                    0x6B
#define MIDI_CONTROL_UNDEFINED_6C                    0x6C
#define MIDI_CONTROL_UNDEFINED_6D                    0x6D
#define MIDI_CONTROL_UNDEFINED_6E                    0x6E
#define MIDI_CONTROL_UNDEFINED_6F                    0x6F
#define MIDI_CONTROL_UNDEFINED_70                    0x70
#define MIDI_CONTROL_UNDEFINED_71                    0x71
#define MIDI_CONTROL_UNDEFINED_72                    0x72
#define MIDI_CONTROL_UNDEFINED_73                    0x73
#define MIDI_CONTROL_UNDEFINED_74                    0x74
#define MIDI_CONTROL_UNDEFINED_75                    0x75
#define MIDI_CONTROL_UNDEFINED_76                    0x76
#define MIDI_CONTROL_UNDEFINED_77                    0x77

// Channel Mode Messages
#define MIDI_CHANNEL_MODE_ALL_SOUND_OFF              0x78
#define MIDI_CHANNEL_MODE_RESET_ALL_CONTROLLERS      0x79
#define MIDI_CHANNEL_MODE_LOCAL_CONTROL_ON_OFF       0x7A
#define MIDI_CHANNEL_MODE_ALL_NOTES_OFF              0x7B
#define MIDI_CHANNEL_MODE_OMNI_MODE_OFF              0x7C
#define MIDI_CHANNEL_MODE_OMNI_MODE_ON               0x7D
#define MIDI_CHANNEL_MODE_MONO_MODE_ON               0x7E
#define MIDI_CHANNEL_MODE_POLY_MODE_ON               0x7F


/** Standard key press velocity value used for all note events, as no pressure sensor is mounted. */
#define MIDI_STANDARD_VELOCITY    100

void midi_init(void);
void midi_noteon(uint8_t note, uint8_t velocity, uint8_t channel);
void midi_noteoff(uint8_t note, uint8_t velocity, uint8_t channel);
void midi_control_change(uint8_t channel, uint8_t control, uint8_t value);

void midi_all_sound_off();
void midi_reset_all_controllers();
void midi_local_control_on();
void midi_local_control_off();
void midi_all_notes_off();
void midi_omni_mode_off();
void midi_omni_mode_on();
void midi_mono_mode_on(uint8_t nchannels);
void midi_poly_mode_on();


#endif /* MIDI_H_ */
