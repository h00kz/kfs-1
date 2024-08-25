#ifndef KERNEL_H
#define KERNEL_H

#define VGA_ADDRESS 0xB8000 // VGA text buffer address


typedef signed char        int8_t;
typedef short              int16_t;
typedef int                int32_t;
typedef long long          int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t;
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;

typedef unsigned long       size_t;


static const long VGA_WIDTH = 80;
static const long VGA_HEIGHT = 25;

size_t terminal_row = 0;
size_t terminal_column = 0;
uint8_t terminal_color = 0;
uint16_t* terminal_buffer = 0;

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

static inline size_t strlen(const int8_t* str)
{
    size_t len = 0;
    while (str[len])
        len++;
    return len;
}

static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline uint16_t vga_entry(uint8_t uc, uint8_t color) 
{
	return (uint16_t) uc | (uint16_t) color << 8;
}

void terminal_init(void);
void terminal_putchar_at(uint8_t c, uint8_t color, size_t col, size_t row);
void terminal_putchar(int8_t c);
void terminal_write_size(const int8_t *str, size_t size);
void terminal_set_colors(enum vga_color fg_color, enum vga_color bg_color);
void terminal_putstr(const int8_t *str);
void terminal_clear(void);

#endif