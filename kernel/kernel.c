#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"

void kernel_main() {
    clear_screen();
    kprintln("Installing ISR's");
    isr_install();

    asm volatile("sti");
    init_timer(50);
    init_keyboard();
}
