#include "vga/vga.h"
#include "gdt/gdt.h"
#include "../lib/libk/libk.h"

void unit_test_vj(void)
{
    /*katoi testin*/
    term_print("katoi:\n");
    size_t i = katoi("-123"); 
    term_set_colors(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK);   
    kputnbr(i);

    /*kitoa testin*/
    term_set_colors(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK); 
    term_print("\n\nkitoa:\n");

    char *s = kitoa(-12, s);

    term_set_colors(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK);
    term_print(s);

    /*kstrncmp testin*/
    term_set_colors(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK); 
    term_print("\n\nkstrncmp:\n");

    char *s1 = "hahaha";
    char *s2 = "hahai"; 
    i = kstrncmp(s1, s2, 6);
    term_set_colors(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK);
    kputnbr(i);

    /*kprintf testin*/
    term_set_colors(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK); 
    term_print("\n\nkprintf:\n");

    term_set_colors(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK);
    char *p = "test";
    kprintf("char: %c, str: %s, *p: %p", 'a', "abc", p);
    term_print("\n");
    kprintf("int: %d, octal: %o, hexa: %x, HEXA: %X", 42, 42, 42, 42);
}

void kernel_main(void)
{
    gdt_init();
    term_init();

    term_banner();

    // tests
    unit_test_vj();
    
    while (1)
    {}
    return;
}