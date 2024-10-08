#pragma once

#include "../types.h"

size_t  kstrlen(const char *str);
void    kputnbr(long int n);
void    term_putchar(const char c);
char	*kitoa(long int n, char *str);
int64_t  katoi(const char *str);
void	*kmemset(char *s, int c, size_t n);
int     kstrncmp(const char *s1, const char *s2, size_t n);
void    kprintf(const char *format, ...);
void print_hex_dump(uint32_t addr, size_t limit);
