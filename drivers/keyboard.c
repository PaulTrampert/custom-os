#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/unused.h"


static void keyboard_callback(registers_t *r) {
  uint8_t scancode = port_byte_in(0x60);
  UNUSED(r);
}

void init_keyboard() {
  register_interrupt_handler(IRQ1, keyboard_callback);
}