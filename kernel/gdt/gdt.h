#pragma once
#include "../../lib/types.h"

struct gdt_entry_s
{
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access_byte;
    uint8_t flags;
    uint8_t base_high;
} __attribute__((packed));

struct gdt_ptr_s
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

typedef struct gdt_entry_s gdt_entry_t;
typedef struct gdt_ptr_s gdt_ptr_t;

void gdt_init(void);
void set_gdt_gate(uint32_t seg_num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
