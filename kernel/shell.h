#pragma once
#include "../drivers/keyboard.h"
#include "../drivers/scancodes.h"
#include <stdint.h>


void init_shell();
void handle_key_down(kbd_event_t *event);
void handle_key_up(kbd_event_t *event);