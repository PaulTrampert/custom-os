#pragma once
#include <stdint.h>

typedef struct {
    uint8_t scancode[4];
    uint8_t keycode;
} kbd_event_t;



void init_keyboard();