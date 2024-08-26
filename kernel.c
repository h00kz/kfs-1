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
    terminal_column = 0;

    if (terminal_row < VGA_HEIGHT - 1)
    {
        terminal_row++;
        return;
    }

    for (size_t row = 1; row < VGA_HEIGHT; ++row)
    {
        for (size_t col = 0; row < VGA_WIDTH; ++col)
        {
            uint16_t _char = terminal_buffer[row * VGA_WIDTH + col];
            terminal_buffer[(row - 1) * VGA_WIDTH + col] = _char;
        }
    }
    terminal_clear_row(VGA_WIDTH - 1);
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
    terminal_column = 0;
    terminal_row = 0;
}

void terminal_clear_row(size_t row)
{
    size_t index = 0;
    for (size_t col = 0; col < VGA_WIDTH; ++col)
    {
        index = row * VGA_WIDTH + col;
        terminal_buffer[index] = vga_entry(' ', terminal_color);
    }
}

void terminal_clear(void)
{
    size_t index = 0;
    for (size_t row = 0; row < VGA_HEIGHT; ++row)
        terminal_clear_row(row);

    terminal_column = 0;
    terminal_row = 0;
}

void update_cursor(int col, int row)
{
	uint16_t pos = row * VGA_WIDTH + col;

	outb(0x3D4, 0x0F); // sélectionne le registre bas du curseur.
	outb(0x3D5, (uint8_t) (pos & 0xFF)); // Envoie les 8bits de poids faible de pos au port 0x3D5. (crtc)
	outb(0x3D4, 0x0E); // sélectionne le registre haut du curseur.
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF)); // Envoie les 8bits de poids fort de pos au port 0x3D5. (crtc)
}

// LOOOOOOOOOOOOOOOOOOL
static void sleep(size_t time)
{
    for (size_t i; i < time * 10000; ++i)
        ;
}

static uint8_t get_scancode()
{
    uint8_t scancode = inb(0x60);
    return scancode;
}

// ENCORE LOOOOOOOOOOOOOOOOOOOOOL
void keyboard_handler(void)
{
    uint8_t scancode = 0;
    scancode = get_scancode();
    if (scancode == KEY_LEFT_ARROW)
    {
        if (terminal_column > 0)
            terminal_column--;
    }
    else if (scancode == KEY_RIGHT_ARROW)
    {
        if (terminal_column < VGA_WIDTH - 1)
            terminal_column++;
    }
}

void kernel_main(void)
{
    terminal_init();

    // terminal_set_colors(VGA_COLOR_CYAN, VGA_COLOR_DARK_GREY);
    terminal_putstr("42\nTEST\n");
    while (1)
    {
        keyboard_handler();
        update_cursor(terminal_column, terminal_row);
        sleep(1000); // LOOOOOOOOOOOOOOOOOLIIIILOOOOOOOOOOOOOOOOOL
    }
    return;
}
