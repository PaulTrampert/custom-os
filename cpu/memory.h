#pragma once
#include <stdint.h>

#define MMAP_ENTRY_SIZE (sizeof(mmap_entry_t))
#define MEM_USABLE 1
#define MEM_RESERVED 2
#define MEM_ACPI_RECLAIMABLE 3
#define MEM_ACPI_NVS 4
#define MEM_BAD 5

typedef struct {
    uint64_t baseAddress;
    uint64_t length;
    uint32_t type;
    uint32_t acpi_ext;
}__attribute__((packed)) mmap_entry_t;


void init_memory(mmap_entry_t *mmap, uint32_t mmap_count);