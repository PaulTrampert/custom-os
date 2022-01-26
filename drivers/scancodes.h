#pragma once
#include <stdint.h>

#define SCD_ERROR 0x00
#define SCD_ESC 0x01
#define SCD_ONE 0x02
#define SCD_TWO 0x03
#define SCD_THREE 0x04
#define SCD_FOUR 0x05
#define SCD_FIVE 0x06
#define SCD_SIX 0x07
#define SCD_SEVEN 0x08
#define SCD_EIGHT 0x09
#define SCD_NINE 0x0A
#define SCD_ZERO 0x0B
#define SCD_MINUS 0x0C
#define SCD_EQUALS 0x0D
#define SCD_BACKSPACE 0x0E
#define SCD_TAB 0x0F
#define SCD_Q 0x10
#define SCD_W 0x11
#define SCD_E 0x12
#define SCD_R 0x13
#define SCD_T 0x14
#define SCD_Y 0x15
#define SCD_U 0x16
#define SCD_I 0x17
#define SCD_O 0x18
#define SCD_P 0x19
#define SCD_OPN_BRKT 0x1A
#define SCD_CLS_BRKT 0x1B
#define SCD_ENTER 0x1C
#define SCD_LCTRL 0x1D
#define SCD_A 0x1E
#define SCD_S 0x1F
#define SCD_D 0x20
#define SCD_F 0x21
#define SCD_G 0x22
#define SCD_H 0x23
#define SCD_J 0x24
#define SCD_K 0x25
#define SCD_L 0x26
#define SCD_SEMICLN 0x27
#define SCD_QUOTE 0x28
#define SCD_TILDE 0x29
#define SCD_LSHIFT 0x2A
#define SCD_BSLASH 0x2B
#define SCD_Z 0x2C
#define SCD_X 0x2D
#define SCD_C 0x2E
#define SCD_V 0x2F
#define SCD_B 0x30
#define SCD_N 0x31
#define SCD_M 0x32
#define SCD_COMMA 0x33
#define SCD_PERIOD 0x34
#define SCD_QUESTION 0x35
#define SCD_RSHIFT 0x36
#define SCD_KPD_STAR 0x37
#define SCD_LALT 0x38
#define SCD_SPACE 0x39
#define SCD_CAPSLOCK 0x3A
#define SCD_F1 0x3B
#define SCD_F2 0x3C
#define SCD_F3 0x3D
#define SCD_F4 0x3E
#define SCD_F5 0x3F
#define SCD_F6 0x40
#define SCD_F7 0x41
#define SCD_F8 0x42
#define SCD_F9 0x43
#define SCD_F10 0x44
#define SCD_NUMLOCK 0x45
#define SCD_SCROLLLOCK 0x46
#define SCD_KPD7 0x47
#define SCD_KPD8 0x48
#define SCD_KPD9 0x49
#define SCD_KPDMINUS 0x4A
#define SCD_KPD4 0x4B
#define SCD_KPD5 0x4C
#define SCD_KPD6 0x4D
#define SCD_KPDPLUS 0x4E
#define SCD_KPD1 0x4F
#define SCD_KPD2 0x50
#define SCD_KPD3 0x51
#define SCD_KPD0 0x52
#define SCD_KPDPERIOD 0x53
#define SCD_RALT 0x54
#define SCD_55 0x55
#define SCD_56 0x56
#define SCD_F11 0x57
#define SCD_F12 0x58
#define SCD_ESCAPE_CODE 0xE0
#define SCD_ESCAPE_CODE2 0xE1

/* Gives the original scancode for a release scancode */
#define SCD_ORIG(scancode) ((uint8_t)scancode - 0x80)

/* TRUE if the given scancode is a release scancode */
#define SCD_IS_RELEASE(scancode) ((uint8_t)scancode > 0x80)

#define SCD_MAPPABLE(scancode) (SCD_IS_RELEASE(scancode) ? SCD_ORIG(scancode) : scancode)

#define KCD_ESC 0x01
#define KCD_ONE 0x02
#define KCD_TWO 0x03
#define KCD_THREE 0x04
#define KCD_FOUR 0x05
#define KCD_FIVE 0x06
#define KCD_SIX 0x07
#define KCD_SEVEN 0x08
#define KCD_EIGHT 0x09
#define KCD_NINE 0x0A
#define KCD_ZERO 0x0B
#define KCD_MINUS 0x0C
#define KCD_EQUALS 0x0D
#define KCD_BACKSPACE 0x0E
#define KCD_TAB 0x0F
#define KCD_Q 0x10
#define KCD_W 0x11
#define KCD_E 0x12
#define KCD_R 0x13
#define KCD_T 0x14
#define KCD_Y 0x15
#define KCD_U 0x16
#define KCD_I 0x17
#define KCD_O 0x18
#define KCD_P 0x19
#define KCD_OPN_BRKT 0x1A
#define KCD_CLS_BRKT 0x1B
#define KCD_ENTER 0x1C
#define KCD_LCTRL 0x1D
#define KCD_A 0x1E
#define KCD_S 0x1F
#define KCD_D 0x20
#define KCD_F 0x21
#define KCD_G 0x22
#define KCD_H 0x23
#define KCD_J 0x24
#define KCD_K 0x25
#define KCD_L 0x26
#define KCD_SEMICLN 0x27
#define KCD_QUOTE 0x28
#define KCD_TILDE 0x29
#define KCD_LSHIFT 0x2A
#define KCD_BSLASH 0x2B
#define KCD_Z 0x2C
#define KCD_X 0x2D
#define KCD_C 0x2E
#define KCD_V 0x2F
#define KCD_B 0x30
#define KCD_N 0x31
#define KCD_M 0x32
#define KCD_COMMA 0x33
#define KCD_PERIOD 0x34
#define KCD_FSLASH 0x35
#define KCD_RSHIFT 0x36
#define KCD_KPD_STAR 0x37
#define KCD_LALT 0x38
#define KCD_SPACE 0x39
#define KCD_CAPSLOCK 0x3A
#define KCD_F1 0x3B
#define KCD_F2 0x3C
#define KCD_F3 0x3D
#define KCD_F4 0x3E
#define KCD_F5 0x3F
#define KCD_F6 0x40
#define KCD_F7 0x41
#define KCD_F8 0x42
#define KCD_F9 0x43
#define KCD_F10 0x44
#define KCD_NUMLOCK 0x45
#define KCD_SCROLLLOCK 0x46
#define KCD_KPD7 0x47
#define KCD_KPD8 0x48
#define KCD_KPD9 0x49
#define KCD_KPDMINUS 0x4A
#define KCD_KPD4 0x4B
#define KCD_KPD5 0x4C
#define KCD_KPD6 0x4D
#define KCD_KPDPLUS 0x4E
#define KCD_KPD1 0x4F
#define KCD_KPD2 0x50
#define KCD_KPD3 0x51
#define KCD_KPD0 0x52
#define KCD_KPDPERIOD 0x53
#define KCD_55 0x55
#define KCD_56 0x56
#define KCD_F11 0x57
#define KCD_F12 0x58
#define KCD_KPDENTER 96
#define KCD_RCTRL 97
#define KCD_KPDFSLASH 98
#define KCD_PRTSC 99
#define KCD_RALT 100
#define KCD_HOME 102
#define KCD_UP 103
#define KCD_PGUP 104
#define KCD_LEFT 105
#define KCD_RIGHT 106
#define KCD_END 107
#define KCD_DOWN 108
#define KCD_PGDN 109
#define KCD_INSERT 110
#define KCD_DEL 111
#define KCD_PAUSE 119

uint8_t scd_to_kcd(uint8_t scd[], uint8_t length);

extern uint8_t esc_scd_tbl[256];

extern uint8_t ascii_tbl[256];
