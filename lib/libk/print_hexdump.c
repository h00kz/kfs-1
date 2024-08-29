#include "../../kernel/vga/vga.h"
#include "libk.h"

void print_hex_dump(uint32_t addr, size_t limit)
{
    limit = kstrlen(addr);
    int j = 0;
    const char *array = (uint32_t *)addr;

    kprintf("\n");
    kprintf("%p | ", array);
    for (size_t i = 0; i < limit; i++)
    {
        if (j >= (VGA_WIDTH - 11) / 2)
        {
            kprintf("|\n%p | ", array);
            j = 0;
        }
        else
        {
            kprintf("%X ", array[i]);
            j += 3;
        }
    }
    term_print("\n---------| ");
    for (size_t i = 0; i < (VGA_WIDTH - 7) / 2; i++)
        term_putchar('-');
    term_print("|\n");    
    j = 0;
    kprintf("%p | ", array);
    for (size_t i = 0; i < limit; i++)
    {
        if (j >= (VGA_WIDTH - 11) / 2)
        {
            kprintf("|\n%p | ", array);
            j = 0;
        }
        else
        {
            kprintf("%c  ", array[i]);
            j += 3;
        }
    }
}