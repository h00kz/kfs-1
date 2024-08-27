#include "vga/vga.h"
//#include "../lib//libasm/libasm.h"

void unit_test_vj(void)
{
  size_t i = ft_strlen("Hellofff fff"); 
  term_set_colors(VGA_COLOR_LIGHT_BLUE, VGA_COLOR_BLACK);
  ft_putnbr(i);
}

void kernel_main(void)
{
    term_init();

    term_print("        :::      ::::::::\n");
    term_print("      :+:      :+:    :+:\n");
    term_print("    +:+ +:+         +:+  \n");
    term_print("  +#+  +:+       +#+     \n");
    term_print("+#+#+#+#+#+   +#+        \n");
    term_print("     #+#    #+#          \n");
    term_print("    ###   ##########     \n");

//tests
    unit_test_vj();
    
    while (1)
    {}
    return;
}
