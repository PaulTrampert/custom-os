#include <stdint.h>
#include "memory.h"
#include "../drivers/screen.h"
#include "../libc/mem.h"
#include "../libc/strings.h"

static char *types[] = {
    "Undefined",
    "Usable",
    "Reserved",
    "ACPI Reclaimable",
    "ACPI NVS",
    "BAD BLOCK"
};

void init_memory(mmap_entry_t *mmap, uint32_t mmap_count) {
    int i;
    char hexStr[32];
    for (i = 0; i < mmap_count; i++) {
        mmap_entry_t *current_entry = &mmap[i];
        memory_set(hexStr, 0, 32);
        kprint("mem-block: ");
        hex_to_ascii(current_entry->baseAddress, hexStr);
        kprint(hexStr);
        memory_set(hexStr, 0, 32);
        uint64_t endAddr = current_entry->baseAddress + current_entry->length;
        hex_to_ascii(endAddr, hexStr);
        kprint("-");
        kprint(hexStr);
        memory_set(hexStr, 0, 32);
        kprint(" type: ");
        kprintln(types[current_entry->type]);
    }
}