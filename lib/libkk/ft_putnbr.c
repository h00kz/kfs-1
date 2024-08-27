#include "../../kernel/vga/vga.h"

void	ft_putnbr(int n)
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
		ft_putnbr(nbl / 10);
		term_putchar(nbl % 10 + '0');
	}
}