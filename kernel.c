#include "kernel.h"

void terminal_init(void)
{
    terminal_row = 0;
    terminal_column = 0;
    terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
    terminal_buffer = (uint16_t*) VGA_ADDRESS;
    size_t index = 0;
    for (size_t row = 0; row < VGA_HEIGHT; ++row)
    {
        for (size_t column = 0; column < VGA_WIDTH; ++column)
        {
            index = row * VGA_WIDTH + column;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
}

void terminal_putchar_at(uint8_t c, uint8_t color, size_t col, size_t row)
{
    size_t index = row * VGA_WIDTH + col;
    terminal_buffer[index] = vga_entry(c, color);
}

void terminal_putchar(char c)
{
    if (c == '\n')
    {
        terminal_newline();
        return;
    }
    terminal_putchar_at(c, terminal_color, terminal_column, terminal_row);
    if (++terminal_column == VGA_WIDTH)
    {
        terminal_column = 0;
        if (++terminal_row == VGA_HEIGHT)
            terminal_row = 0;
    }
}

void terminal_newline(void)
{
    return;
}

void terminal_write_size(const char* str, size_t size)
{
    for (size_t i = 0; i < size; ++i)
        terminal_putchar(str[i]);
}

void terminal_set_colors(enum vga_color fg_color, enum vga_color bg_color)
{
    terminal_color = fg_color| bg_color << 4;
}

void terminal_putstr(const char* str)
{
    terminal_write_size(str, strlen(str));
}

void terminal_clear(void)
{
    size_t index = 0;
    for (size_t row = 0; row < VGA_HEIGHT; ++row)
    {
        for (size_t col = 0; col < VGA_WIDTH; ++col)
        {
            index = row * VGA_WIDTH + col;
            terminal_buffer[index] = vga_entry(' ', terminal_color);
        }
    }
    terminal_column = 0;
    terminal_row = 0;
}

void kernel_main(void)
{
    terminal_init();

    terminal_set_colors(VGA_COLOR_CYAN, VGA_COLOR_DARK_GREY);
    terminal_putstr("42");
    return;
}
