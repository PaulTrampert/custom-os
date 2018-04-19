#include "../drivers/screen.h"
#include "util.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"

void kernel_main() {
    clear_screen();
    kprintln("Installing ISR's");
    isr_install();

    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
}
