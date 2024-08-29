#pragma once
#include "../../lib/types.h"

extern void ioport_out(uint16_t port, uint8_t value);
extern char ioport_in(uint16_t port);
extern void keyboard_handler(void);
extern void enable_int(void);


#define PIC1            0x20        // IO base address for master PIC
#define PIC2            0xA0        // IO base address for slave PIC
#define PIC1_COMMAND    PIC1
#define PIC1_DATA       (PIC1 + 1)
#define PIC2_COMMAND    PIC2
#define PIC2_DATA       (PIC2 + 1)

struct idt_entry_s {
    uint16_t base_low;
    uint16_t seg_selector;
    uint8_t always0;
    uint8_t attributes;
    uint16_t base_high;
} __attribute__((packed));

struct idt_ptr_s {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

typedef struct idt_entry_s idt_entry_t;
typedef struct idt_ptr_s idt_ptr_t;

void idt_init(void);
void set_idt_gate(uint8_t n, uint32_t base, uint16_t seg_selector, uint8_t flags);