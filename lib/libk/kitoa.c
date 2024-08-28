#include "../../kernel/vga/vga.h"
#include "libk.h"

long int	isnegative(long int n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

size_t	chain_size(size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char    *kitoa(long int n, char *str)
{
	long int	nb = isnegative(n);
	size_t      i = chain_size(nb);
    
    kmemset(str, 0, i + 1);
	if (n < 0)
		i++;
	if (nb == 0)
		return (0);
	str[i] = '\0';
	while (i > 0)
	{
		i--;
		str[i] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}