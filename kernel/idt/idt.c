#include "idt.h"
#include "../../lib/libk/libk.h"

// JAIME LA VIE

idt_entry_t idt_entries[256];
idt_ptr_t idt_ptr;

extern void load_idt(uint8_t* idt_addr);

void idt_init(void)
{
    idt_ptr.limit = sizeof(idt_entry_t) * 256 - 1;
    idt_ptr.base = (uint32_t) &idt_entries;

    kmemset((char*)&idt_entries, 0, sizeof(idt_entry_t) * 256);
    // PICs : Programmable Interrupt Controllers

    ioport_out(PIC1_COMMAND, 0x11); // PIC master, commande d'init (ICW1)
    ioport_out(PIC2_COMMAND, 0x11); // PIC slave, commande d'init (ICW1)

    ioport_out(PIC1_DATA, 0x20); // offset vector d'interrupt pour le PIC master (0x20 - 0x27)
    ioport_out(PIC2_DATA, 0x28); // offset vector d'interrupt pour le PIC slave (0x28 - 0x2f)

    ioport_out(PIC1_DATA, 0x04); // mode auto pour le PIC master
    ioport_out(PIC2_DATA, 0x02); // mode auto pour le PIC slave


    ioport_out(PIC1_DATA, 0x01); // 8086/88 mode (proc)
    ioport_out(PIC2_DATA, 0x01); // pareil

    ioport_out(PIC1_DATA, 0x0); // null jsp j'essaie
    ioport_out(PIC2_DATA, 0x0); // null
	// ioport_out(PIC1_DATA, 0xff);
	// ioport_out(PIC2_DATA, 0xff);


    set_idt_gate(33, (uint32_t)keyboard_handler, 0x08, 0x8e);

    load_idt((uint8_t*)&idt_ptr);
}


void set_idt_gate(uint8_t n, uint32_t base, uint16_t seg_selector, uint8_t flags)
{
    idt_entries[n].base_low = base & 0x0000ffff;
    idt_entries[n].seg_selector = seg_selector;
    idt_entries[n].always0 = 0;
    idt_entries[n].attributes = flags | 0x60;
    idt_entries[n].base_high = (base & 0xffff0000) >> 16;
}