#include "../../kernel/vga/vga.h"
#include "libk.h"
#include <stdarg.h>

void kprintf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    for (const char *p = format; *p != '\0'; p++) 
    {
        if (*p == '%') 
        {
            p++;
            if (*p == 's') 
            {
                char *str = va_arg(args, char *);
                while (*str) {
                    term_putchar(*str++);
                }
            } 
            else if (*p == 'd') 
            {
                int i = va_arg(args, int);
                char buffer[20];
                kitoa(i, buffer);
                char *str = buffer;
                while (*str) {
                    term_putchar(*str++);
                }
            }
            else if (*p == 'c')
            {
                char c = va_arg(args, int);
                term_putchar(c);
            } 
            else 
            {
                term_putchar('%');
                term_putchar(*p);
            }
        } 
        else 
        {
            term_putchar(*p);
        }
    }

    va_end(args);
}