#pragma once

#include "../../lib/types.h"


#define VGA_ADDRESS 0xB8000 // VGA text buffer address

typedef struct char_s
{
    char character;
    uint8_t color;
} char_t;


static const long VGA_WIDTH = 80;
static const long VGA_HEIGHT = 25;

// -------------------- COLORS
enum vga_color {
    VGA_COLOR_BLACK = 0,
    VGA_COLOR_BLUE = 1,
    VGA_COLOR_GREEN = 2,
    VGA_COLOR_CYAN = 3,
    VGA_COLOR_RED = 4,
    VGA_COLOR_MAGENTA = 5,
    VGA_COLOR_BROWN = 6,
    VGA_COLOR_LIGHT_GREY = 7,
    VGA_COLOR_DARK_GREY = 8,
    VGA_COLOR_LIGHT_BLUE = 9,
    VGA_COLOR_LIGHT_GREEN = 10,
    VGA_COLOR_LIGHT_CYAN = 11,
    VGA_COLOR_LIGHT_RED = 12,
    VGA_COLOR_LIGHT_MAGENTA = 13,
    VGA_COLOR_LIGHT_BROWN = 14, 
    VGA_COLOR_WHITE = 15,
};
// -----------------------------


// ------------- FUNC PROTOTYPES
void prompt(char c);
size_t get_term_col(void);
size_t get_term_row(void);
void set_term_col(size_t v);
void set_term_row(size_t v);
void term_banner(void);
void term_init(void);
void term_newline(void);
void term_putchar(const char c);
void term_print(const char *str);
void term_clear_row(size_t row);
void term_clear(void);
void term_set_colors(enum vga_color fg_color, enum vga_color bg_color);
// -----------------------------
