#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "shell.h"

void kernel_main() {
    clear_screen();
    kprintln("Installing ISR's...");
    isr_install();
    kprintln("Initializing timer...");
    init_timer(50);
    kprintln("Initializing keyboard driver...");
    init_keyboard();
    kprintln("Starting shell...");
    init_shell();
    kprintln("Welcome to POS (Paul's OS)");
    asm volatile("sti");
}

