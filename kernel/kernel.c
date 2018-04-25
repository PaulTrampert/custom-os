#include <stdint.h>
#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"
#include "shell.h"

void kernel_main(uint32_t mmap_location, uint32_t mmap_count) {
    clear_screen();
    kprintln("Installing ISR's...");
    isr_install();
    kprintln("Initializing timer...");
    init_timer(50);
    kprintln("Initializing keyboard driver...");
    init_keyboard();
    kprintln("Starting shell...");
    init_shell();
    asm volatile("sti");
}

