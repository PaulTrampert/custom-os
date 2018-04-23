#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../libc/unused.h"
#include "../libc/strings.h"
#include "../libc/mem.h"
#include "scancodes.h"

static uint8_t escaped = 0;
static uint8_t scd_buffer[] = {'\0', '\0', '\0', '\0'};
static bool keystates[256];

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

  memory_set(ascii_tbl, (uint8_t)0, 256);
  ascii_tbl[KCD_TAB] = '\t';
  ascii_tbl[KCD_ENTER] = '\n';
  ascii_tbl[KCD_SPACE] = ' ';
  ascii_tbl[KCD_QUOTE] = '\'';
  ascii_tbl[KCD_TILDE] = '`';
  ascii_tbl[KCD_MINUS] = '-';
  ascii_tbl[KCD_PERIOD] = '.';
  ascii_tbl[KCD_FSLASH] = '/';
  ascii_tbl[KCD_ZERO] = '0';
  ascii_tbl[KCD_ONE] = '1';
  ascii_tbl[KCD_TWO] = '2';
  ascii_tbl[KCD_THREE] = '3';
  ascii_tbl[KCD_FOUR] = '4';
  ascii_tbl[KCD_FIVE] = '5';
  ascii_tbl[KCD_SIX] = '6';
  ascii_tbl[KCD_SEVEN] = '7';
  ascii_tbl[KCD_EIGHT] = '8';
  ascii_tbl[KCD_NINE] = '9';
  ascii_tbl[KCD_SEMICLN] = ';';
  ascii_tbl[KCD_EQUALS] = '=';
  
}

void init_keyboard() {
  us_std_kbd();
  register_interrupt_handler(IRQ1, keyboard_callback);
}