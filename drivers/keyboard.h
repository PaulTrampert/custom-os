#pragma once
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t scancode[4];
    uint8_t keycode;
    uint8_t ascii;
} kbd_event_t;



void init_keyboard();