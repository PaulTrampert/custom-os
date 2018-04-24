#include "../drivers/keyboard.h"
#include "../drivers/scancodes.h"
#include "../libc/mem.h"
#include "shell.h"
#include <stdbool.h>
#include "../drivers/screen.h"
#include "../libc/strings.h"

static bool isLShiftDown = false;
static bool isRShiftDown = false;
static bool capsLock = false;
static bool numLock = false;

#define IS_SHIFT_DOWN (isLShiftDown || isRShiftDown)
#define IS_UPPER_CASE(c) (c >= 0x41 && c <=0x5A)
#define IS_LOWER_CASE(c) (c >=0x61 && c <= 0x7A)
#define TO_LOWER_CASE(c) (c + 0x20)
#define TO_UPPER_CASE(c) (c - 0x20)
#define IS_ALPHA(c) (IS_UPPER_CASE(c) || IS_LOWER_CASE(c))
#define BUFFER_SIZE 80

uint8_t buffer[BUFFER_SIZE];
uint8_t bufferOffset = 0;

static bool is_numlock_affected(uint8_t keycode) {
  return (
    keycode == KCD_KPD_STAR || 
    (keycode >= 0x47 && keycode <= 0x53) ||
    keycode == 96 ||
    keycode == 98
  );
}

static void handle_standard_key(kbd_event_t *event) {
  uint8_t c = 0;
  if (
    IS_SHIFT_DOWN || 
    (numLock && is_numlock_affected(event->keycode))
  ) {
    c = shift_ascii_tbl[event->keycode];
  }
  else {
    c = ascii_tbl[event->keycode];
  }
  if (c && bufferOffset < BUFFER_SIZE) {
    if (capsLock && IS_ALPHA(c)) {
      if (IS_UPPER_CASE(c)) {
        c = TO_LOWER_CASE(c);
      }
      else {
        c = TO_UPPER_CASE(c);
      }
    }
    uint8_t str[2] = {c, 0};
    buffer[bufferOffset++] = c;
    kprint(str);
  }
}

static void handle_enter(){
  kprint("\n");
  if (strcompare(buffer, "end") == 0) {
    kprintln("Goodbye!");
    asm volatile("hlt");
  }
  else {
    kprint(buffer);
    kprintln(" is not a recognized command or program.");
  }
  memory_set(buffer, 0, BUFFER_SIZE);
  bufferOffset = 0;
}

static void handle_backspace() {
  if (bufferOffset) {
    kbackspace();
    buffer[--bufferOffset] = 0;
  }
}

void handle_key_down(kbd_event_t *event) {
    switch(event->keycode) {
      case KCD_CAPSLOCK:
        capsLock = !capsLock;
        break;
      case KCD_NUMLOCK:
        numLock = !numLock;
        break;
      case KCD_LSHIFT:
        isLShiftDown = true;
        break;
      case KCD_RSHIFT:
        isRShiftDown = true;
        break;
      case KCD_BACKSPACE:
        handle_backspace();
        break;
      case KCD_ENTER:
      case KCD_KPDENTER:
        handle_enter();
      case KCD_TAB:
        break;
      default:
        handle_standard_key(event);
    }
}

void handle_key_up(kbd_event_t *event) {
  switch(event->keycode) {
    case KCD_LSHIFT:
      isLShiftDown = false;
      break;
    case KCD_RSHIFT:
      isRShiftDown = false;
      break;
    default:
      return;
  }
}

void init_shell() {
  memory_set(buffer, 0, BUFFER_SIZE);
  // Init base ascii table
  memory_set(ascii_tbl, 0, 256);
  ascii_tbl[KCD_TAB] = '\t';
  ascii_tbl[KCD_ENTER] = '\n';
  ascii_tbl[KCD_SPACE] = ' ';
  ascii_tbl[KCD_QUOTE] = '\'';
  ascii_tbl[KCD_COMMA] = ',';
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
  ascii_tbl[KCD_OPN_BRKT] = '[';
  ascii_tbl[KCD_BSLASH] = '\\';
  ascii_tbl[KCD_CLS_BRKT] = ']';
  ascii_tbl[KCD_TILDE] = '`';
  ascii_tbl[KCD_A] = 'a';
  ascii_tbl[KCD_B] = 'b';
  ascii_tbl[KCD_C] = 'c';
  ascii_tbl[KCD_D] = 'd';
  ascii_tbl[KCD_E] = 'e';
  ascii_tbl[KCD_F] = 'f';
  ascii_tbl[KCD_G] = 'g';
  ascii_tbl[KCD_H] = 'h';
  ascii_tbl[KCD_I] = 'i';
  ascii_tbl[KCD_J] = 'j';
  ascii_tbl[KCD_K] = 'k';
  ascii_tbl[KCD_L] = 'l';
  ascii_tbl[KCD_M] = 'm';
  ascii_tbl[KCD_N] = 'n';
  ascii_tbl[KCD_O] = 'o';
  ascii_tbl[KCD_P] = 'p';
  ascii_tbl[KCD_Q] = 'q';
  ascii_tbl[KCD_R] = 'r';
  ascii_tbl[KCD_S] = 's';
  ascii_tbl[KCD_T] = 't';
  ascii_tbl[KCD_U] = 'u';
  ascii_tbl[KCD_V] = 'v';
  ascii_tbl[KCD_W] = 'w';
  ascii_tbl[KCD_X] = 'x';
  ascii_tbl[KCD_Y] = 'y';
  ascii_tbl[KCD_Z] = 'z';

  // Init shift ascii table
  memory_set(shift_ascii_tbl, 0, 256);
  shift_ascii_tbl[KCD_TAB] = '\t';
  shift_ascii_tbl[KCD_ENTER] = '\n';
  shift_ascii_tbl[KCD_SPACE] = ' ';
  shift_ascii_tbl[KCD_ONE] = '!';
  shift_ascii_tbl[KCD_QUOTE] = '"';
  shift_ascii_tbl[KCD_THREE] = '#';
  shift_ascii_tbl[KCD_FOUR] = '$';
  shift_ascii_tbl[KCD_FIVE] = '%';
  shift_ascii_tbl[KCD_SEVEN] = '&';
  shift_ascii_tbl[KCD_NINE] = '(';
  shift_ascii_tbl[KCD_ZERO] = ')';
  shift_ascii_tbl[KCD_EIGHT] = '*';
  shift_ascii_tbl[KCD_KPD_STAR] = '*';
  shift_ascii_tbl[KCD_EQUALS] = '+';
  shift_ascii_tbl[KCD_KPDPLUS] = '+';
  shift_ascii_tbl[KCD_KPDMINUS] = '-';
  shift_ascii_tbl[KCD_KPDPERIOD] = '.';
  shift_ascii_tbl[KCD_KPDFSLASH] = '/';
  shift_ascii_tbl[KCD_KPD0] = '0';
  shift_ascii_tbl[KCD_KPD1] = '1';
  shift_ascii_tbl[KCD_KPD2] = '2';
  shift_ascii_tbl[KCD_KPD3] = '3';
  shift_ascii_tbl[KCD_KPD4] = '4';
  shift_ascii_tbl[KCD_KPD5] = '5';
  shift_ascii_tbl[KCD_KPD6] = '6';
  shift_ascii_tbl[KCD_KPD7] = '7';
  shift_ascii_tbl[KCD_KPD8] = '8';
  shift_ascii_tbl[KCD_KPD9] = '9';
  shift_ascii_tbl[KCD_SEMICLN] = ':';
  shift_ascii_tbl[KCD_COMMA] = '<';
  shift_ascii_tbl[KCD_PERIOD] = '>';
  shift_ascii_tbl[KCD_FSLASH] = '?';
  shift_ascii_tbl[KCD_TWO] = '@';
  shift_ascii_tbl[KCD_A] = 'A';
  shift_ascii_tbl[KCD_B] = 'B';
  shift_ascii_tbl[KCD_C] = 'C';
  shift_ascii_tbl[KCD_D] = 'D';
  shift_ascii_tbl[KCD_E] = 'E';
  shift_ascii_tbl[KCD_F] = 'F';
  shift_ascii_tbl[KCD_G] = 'G';
  shift_ascii_tbl[KCD_H] = 'H';
  shift_ascii_tbl[KCD_I] = 'I';
  shift_ascii_tbl[KCD_J] = 'J';
  shift_ascii_tbl[KCD_K] = 'K';
  shift_ascii_tbl[KCD_L] = 'L';
  shift_ascii_tbl[KCD_M] = 'M';
  shift_ascii_tbl[KCD_N] = 'N';
  shift_ascii_tbl[KCD_O] = 'O';
  shift_ascii_tbl[KCD_P] = 'P';
  shift_ascii_tbl[KCD_Q] = 'Q';
  shift_ascii_tbl[KCD_R] = 'R';
  shift_ascii_tbl[KCD_S] = 'S';
  shift_ascii_tbl[KCD_T] = 'T';
  shift_ascii_tbl[KCD_U] = 'U';
  shift_ascii_tbl[KCD_V] = 'V';
  shift_ascii_tbl[KCD_W] = 'W';
  shift_ascii_tbl[KCD_X] = 'X';
  shift_ascii_tbl[KCD_Y] = 'Y';
  shift_ascii_tbl[KCD_Z] = 'Z';
  shift_ascii_tbl[KCD_SIX] = '^';
  shift_ascii_tbl[KCD_MINUS] = '_';
  shift_ascii_tbl[KCD_OPN_BRKT] = '{';
  shift_ascii_tbl[KCD_BSLASH] = '|';
  shift_ascii_tbl[KCD_CLS_BRKT] = '}';
  shift_ascii_tbl[KCD_TILDE] = '~';
}