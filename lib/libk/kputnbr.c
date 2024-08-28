#include "libk.h"

void	kputnbr(long int n)
{
	long int	nbl;

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