#include "keyboard.h"
#include "ports.h"
#include "../cpu/isr.h"
#include "screen.h"


static void keyboard_callback(registers_t *r) {
  uint8_t scancode = port_byte_in(0x60);

}

void init_keyboard() {
  register_interrupt_handler(IRQ1, keyboard_callback);
}