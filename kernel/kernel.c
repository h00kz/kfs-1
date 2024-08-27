#include "vga/vga.h"
#include "../lib/libkk/libc.h"

void unit_test_vj(void)
{
  size_t i = kstrlen("Hellofff fff"); 
  term_set_colors(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK);
  kputnbr(i);
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
