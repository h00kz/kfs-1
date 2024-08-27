#include "vga.h"

size_t term_row = 0;
size_t term_column = 0;
uint8_t term_color = 0;
char_t* term_buffer = { 0 };

void term_set_colors(enum vga_color fg_color, enum vga_color bg_color)
{
    term_color = fg_color | bg_color << 4;
}

void term_init(void)
{
    term_row = 0;
    term_column = 0;
    term_buffer = (char_t*) VGA_ADDRESS;
    term_set_colors(VGA_COLOR_RED, VGA_COLOR_BLACK);
    for (size_t row = 0; row < VGA_HEIGHT; ++row)
    {
        for (size_t column = 0; column < VGA_WIDTH; ++column)
        {
            char_t _char = {.character = ' ', .color = term_color};
            term_buffer[row * VGA_WIDTH + column] = _char;
        }
    }
}

void term_newline(void)
{
    term_column = 0;

    if (term_row < VGA_HEIGHT - 1)
    {
        term_row++;
        return;
    }

    for (size_t row = 1; row < VGA_HEIGHT; ++row)
    {
        for (size_t col = 0; row < VGA_WIDTH; ++col)
        {
            char_t _char = term_buffer[row * VGA_WIDTH + col];
            term_buffer[(row - 1) * VGA_WIDTH + col] = _char;
        }
    }
    term_clear_row(VGA_WIDTH - 1);
}

void term_putchar(const char c)
{
    if (term_column == VGA_WIDTH)
        term_newline();
    
    char_t _char = {.character = c, .color = term_color}; 
    term_buffer[term_row * VGA_WIDTH + (term_column++)] = _char;
}

void term_print(const char* str)
{
    while (*str)
    {
        switch (*str)
        {
            case '\n':
                term_newline();
                break;
            case '\r':
                term_column = 0;
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
                term_putchar(*str);
                break;
        }
        str++;
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

void term_clear(void)
{
    size_t index = 0;

    for (size_t row = 0; row < VGA_HEIGHT; ++row)
        term_clear_row(row);

    term_column = 0;
    term_row = 0;
}