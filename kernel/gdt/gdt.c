#include "gdt.h"

gdt_entry_t gdt_entries[5];
gdt_ptr_t gdt_ptr;

extern void flush_gdt(uint8_t* gdt_addr);

void gdt_init(void)
{
    gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
    gdt_ptr.base = (uint32_t)&(gdt_entries);

    set_gdt_gate(0, 0, 0, 0, 0);
    set_gdt_gate(1, 0, 0xffffffff, 0x9a, 0xcf); // kernel code segment
    set_gdt_gate(2, 0, 0xffffffff, 0x92, 0xcf); // kernel data segment
    set_gdt_gate(3, 0, 0xffffffff, 0xfa, 0xcf); // user code segment
    set_gdt_gate(4, 0, 0xffffffff, 0xf2, 0xcf); // user data segment

    flush_gdt((uint8_t*)&(gdt_ptr));
    // 1001 1010 kernel code seg
    //  9    A
    // 1001 0010 kernel data seg
    //  9    2

    // 1111 1010 user code seg
    //  F    A
    // 1111 0010 user data seg
    //  F    2
}

void set_gdt_gate(uint32_t seg_num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt_entries[seg_num].base_low = (base & 0xffff);
    gdt_entries[seg_num].base_mid = (base >> 16) & 0xff;
    gdt_entries[seg_num].base_high = (base >> 24) & 0xff;

    gdt_entries[seg_num].limit = (limit & 0xffff);
    gdt_entries[seg_num].flags = (limit >> 16) & 0x0f;
    gdt_entries[seg_num].flags |= (gran & 0xf0);
    
    gdt_entries[seg_num].access_byte = access;
}