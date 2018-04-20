#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/unused.h"
#include "../libc/strings.h"
#include "scancodes.h"

static uint8_t escaped = 0;

static uint8_t scancode_to_keycode(uint8_t scancode) {

}

static void keyboard_callback(registers_t *r) {
  uint8_t scancode = port_byte_in(0x60);
  if (scancode == SCD_ESCAPE_CODE || scancode == SCD_ESCAPE_CODE2) {
    escaped = 1;
    return;
  }
  else if (SCD_IS_RELEASE(scancode)) {
    // TODO: handle keyup
  }
  else {
    // TODO: handle keydown
  }
  UNUSED(r);
}

void init_keyboard() {
  register_interrupt_handler(IRQ1, keyboard_callback);
}