#include "../../kernel/vga/vga.h"
#include "libk.h"
#include <stdarg.h>

static void itoa_reverse(char *p1, char *p2)
{
    while (p1 < p2) {
        char tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
        p1++;
        p2--;
    }
}

static void itoa_octal(int value, char *str) {
    char *p = str;
    char *p1, *p2;
    int tmp_value;

    if (value < 0) {
        *p++ = '-';
        value = -value;
    }
    p1 = p;
    while (value)
    {
        tmp_value = value;
        value /= 8;
        *p++ = "01234567"[tmp_value - value * 8];
    } ;
    *p = '\0';
    p2 = p - 1;
    itoa_reverse(p1, p2);
}

static void itoa_hexa(int value, char *str, char flag) {
    char *p = str;
    char *p1, *p2;
    int tmp_value;

    if (value < 0) {
        *p++ = '-';
        value = -value;
    }
    p1 = p;
    if (flag == 'p')
        term_print("0x");
    while (value) {
        tmp_value = value;
        value /= 16;
        if (flag == 'x')
            *p++ = "0123456789abcdef"[tmp_value - value * 16];
        else
            *p++ = "0123456789ABCDEF"[tmp_value - value * 16];
    }
    *p = '\0';
    p2 = p - 1;
    itoa_reverse(p1, p2);
}

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
            else if (*p == 'c')
            {   
                char c = va_arg(args, int);
                term_putchar(c);
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
            else if (*p == 'o')
            {
                int i = va_arg(args, int);
                char buffer[20];
                itoa_octal(i, buffer);
                char *str = buffer;
                while (*str) {
                    term_putchar(*str++);
                }
            }
            else if (*p == 'x' || *p == 'X' || *p == 'p')
            {
                int i = va_arg(args, int);
                char buffer[20];
                if (*p == 'x')
                    itoa_hexa(i, buffer, 'x');
                else if (*p == 'X')
                    itoa_hexa(i, buffer, 'X');
                else 
                    itoa_hexa(i, buffer, 'p');
                char *str = buffer;
                while (*str) {
                    term_putchar(*str++);
                }   
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