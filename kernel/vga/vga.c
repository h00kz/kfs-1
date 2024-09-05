#include "vga.h"
#include "../../lib/libk/libk.h"
#include "../idt/idt.h"

size_t term_row = 0;
size_t term_column = 0;
uint8_t term_color = 0;
char_t* term_buffer = { 0 };

void update_cursor(int x, int y)
{
	uint16_t pos = y * VGA_WIDTH + x;

	ioport_out(0x3D4, 0x0F);
	ioport_out(0x3D5, (uint8_t) (pos & 0xFF));
	ioport_out(0x3D4, 0x0E);
	ioport_out(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void term_set_colors(enum vga_color fg_color, enum vga_color bg_color)
{
    term_color = fg_color | bg_color << 4;
}

void term_banner(void)
{
    term_column = 0;
    term_row = 0;
    term_set_colors(VGA_COLOR_RED, VGA_COLOR_BLACK);
    term_print("    :::     ::::::::       :::    ::: :::::::::: ::::::::  \n");
    term_print("   :+:     :+:    :+:      :+:   :+:  :+:       :+:    :+: \n");
    term_print("  +:+ +:+        +:+       +:+  +:+   +:+       +:+        \n");
    term_print(" +#+  +:+      +#+         +#++:++    :#::+::#  +#++:++#++ \n");
    term_print("+#+#+#+#+#+  +#+           +#+  +#+   +#+              +#+ \n");
    term_print("      #+#   #+#            #+#   #+#  #+#       #+#    #+# \n");
    term_print("      ###  ##########      ###    ### ###        ######## ");
    term_set_colors(VGA_COLOR_DARK_GREY, VGA_COLOR_BLACK);
    term_print("\n");
    term_print("by vjavelot & jlarrieu\n\n");
    term_set_colors(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
}

void term_footer(void)
{
    term_set_colors(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    // for (size_t i = 0; i < 10; i++)
    //     term_putchar(' ');
    term_print("     ");
    term_print("TAB: navigate");
    term_print("    ");
    term_print("ENTER: access");
    term_print("     ");
    term_print("F3: return");
    term_print("     ");
    term_print("ESCAPE: exit");
    term_print("\n\n\n");
}

void term_init(void)
{
    term_row = 0;
    term_column = 0;
    term_buffer = (char_t*) VGA_ADDRESS;
    term_set_colors(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    for (size_t row = 0; row < VGA_HEIGHT; ++row)
    {
        for (size_t column = 0; column < VGA_WIDTH; ++column)
        {
            char_t _char = {.character = ' ', .color = term_color};
            term_buffer[row * VGA_WIDTH + column] = _char;
        }
    }
}

void scroll_up(void)
{
    for (size_t row = 0; row < VGA_HEIGHT; row++)
    {
        for (size_t col = 0; col < VGA_WIDTH; col++)
        {
            char_t _char = term_buffer[row * VGA_WIDTH + col];
            term_buffer[(row - 1) * VGA_WIDTH + col] = _char;
        }
    }
    term_clear_row(term_row);
}

void term_newline(void)
{

    if (term_row < VGA_HEIGHT - 1)
    {
        term_row++;
        term_column = 0;
    }
    else
    {
        scroll_up();
        // term_banner();
        term_column = 0;
    }
    return;
}

void term_putchar(const char c)
{
    if (c == '\n')
    {
        term_newline();
        return;
    }
    if (term_column == VGA_WIDTH)
        term_newline();
    
    char_t _char = {.character = c, .color = term_color}; 
    term_buffer[term_row * VGA_WIDTH + (term_column++)] = _char;
    update_cursor(term_column, term_row);
}

void term_print(const char* str)
{
    int i = 0;
    while (str[i])
    {
        switch (str[i])
        {
            case '\n':
                term_newline();
                break;
            case '\r':
                term_column = 0;
                break;
            case '\b':
                if (term_column == 0)
                    return;
                term_column--;
                term_putchar(' ');
                term_column--;
                break;
            case '\t':
                if (term_column == VGA_WIDTH)
                    term_newline();
                
                uint16_t tab_len = 4 - (term_column % 4);
                while (tab_len != 0)
                {
                    term_putchar(' ');
                    tab_len--;
                }
                break;
            default:
                term_putchar(str[i]);
                break;
        }
        i++;
    }
}

void term_clear_row(size_t row)
{
    size_t index = 0;
    for (size_t col = 0; col < VGA_WIDTH; ++col)
    {
        index = row * VGA_WIDTH + col;
        char_t _char = 
        {
            .character = ' ',
            .color = term_color
        };
        term_buffer[index] = _char;
    }
}

size_t get_term_col(void)
{
    return term_column;
}

size_t get_term_row(void)
{
    return term_row;
}

void set_term_col(size_t v)
{
    term_column = v;
}

void set_term_row(size_t v)
{
    term_row = v;
}

static char_t get_char(size_t index)
{
    return term_buffer[index];
}

void prompt(char c)
{
    if (c == '\n')
        term_putchar('\n');
    else if (c == '\b')
    {
        if (term_column == 0 || term_column <= kstrlen("[@kfs-1]> "))
            return;
        term_column--;
        term_putchar(' ');
        term_column--;
        update_cursor(term_column, term_row);
    }
    else if (c == '\t')
    {
        term_print("\t");
        return;
    }
    if (c == -13)
    {
        if (term_column == 0 || term_column <= kstrlen("[@kfs-1]> "))
            return;
        update_cursor(--term_column, term_row);
        return;
    }
    else if (c == -14)
    {
        size_t index = term_row * VGA_WIDTH + term_column;
        char_t _char = {.character = ' ', .color = term_color};
        if (' ' == get_char(index).character)
            return;
        // int len = kstrlen(term_buffer);
        // kprintf("len: %d", len);
        update_cursor(++term_column, term_row);
        return;
    }
    if (c == '\n' || c == 0)
    {
        if (c == 0)
            term_putchar('\n');
        term_set_colors(VGA_COLOR_LIGHT_GREEN, VGA_COLOR_BLACK);
        term_print("[@kfs-1]> ");
        term_set_colors(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
        // update_cursor(term_column, term_row);
    }
    else if (c != '\n' && c != '\b')
        term_putchar(c);
}

void term_clear(void)
{
    size_t index = 0;

    for (size_t row = 0; row < VGA_HEIGHT; ++row)
        term_clear_row(row);

    term_column = 0;
    term_row = 0;
}