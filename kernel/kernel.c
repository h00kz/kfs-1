#include "vga/vga.h"
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
    kprintf("int: %d, char: %c, str: %s", 10, 'a', "abc");

}

void kernel_main(void)
{
    term_init();

    term_banner();

    // tests
    unit_test_vj();
    
    while (1)
    {}
    return;
}