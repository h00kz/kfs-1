#include "../../kernel/vga/vga.h"

void	kputnbr(int n)
{
	size_t	nbl;

	nbl = n;
	if (nbl < 0)
	{
		term_putchar('-');
		nbl = -nbl;
	}
	if (nbl <= 9)
		term_putchar(nbl + '0');
	else
	{
		kputnbr(nbl / 10);
		term_putchar(nbl % 10 + '0');
	}
}