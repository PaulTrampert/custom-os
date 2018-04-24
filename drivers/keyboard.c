#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/unused.h"
#include "../libc/strings.h"
#include "../libc/mem.h"
#include "scancodes.h"
#include "../kernel/shell.h"

static uint8_t escaped = 0;
static uint8_t scd_buffer[] = {'\0', '\0', '\0', '\0'};

static void keyboard_callback(registers_t *r) {
  uint8_t scancode = 0;
  do { scancode = port_byte_in(0x60); } while (scancode == 0);
  if (scancode == SCD_ESCAPE_CODE || scancode == SCD_ESCAPE_CODE2) {
    escaped = (scancode + 1) - 0xE0;
  }
  append(scd_buffer, scancode);
  if (escaped) {
    escaped--;
    return;
  }
  kbd_event_t event = {
    .scancode = scd_buffer,
    .keycode = scd_to_kcd(scd_buffer, strlen(scd_buffer)),
  };
  if (SCD_IS_RELEASE(scancode)) {
    handle_key_up(&event);
  }
  else {
    handle_key_down(&event);
  }
  memory_set(scd_buffer, 0, 4);
  UNUSED(r);
}

static void us_std_kbd(){
  memory_set(esc_scd_tbl, (uint8_t)0, 256);
  esc_scd_tbl[0x1c] = KCD_KPDENTER;
  esc_scd_tbl[0x1d] = KCD_RCTRL;
  esc_scd_tbl[0x35] = KCD_KPDFSLASH;
  esc_scd_tbl[0x2a] = KCD_PRTSC;
  esc_scd_tbl[0x38] = KCD_RALT;
  esc_scd_tbl[0x47] = KCD_HOME;
  esc_scd_tbl[0x48] = KCD_UP;
  esc_scd_tbl[0x49] = KCD_PGUP;
  esc_scd_tbl[0x4b] = KCD_LEFT;
  esc_scd_tbl[0x4d] = KCD_RIGHT;
  esc_scd_tbl[0x4f] = KCD_END;
  esc_scd_tbl[0x50] = KCD_DOWN;
  esc_scd_tbl[0x51] = KCD_PGDN;
  esc_scd_tbl[0x52] = KCD_INSERT;
  esc_scd_tbl[0x53] = KCD_DEL;
}

void init_keyboard() {
  us_std_kbd();
  register_interrupt_handler(IRQ1, keyboard_callback);
}