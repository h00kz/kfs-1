#include "libk.h"

void	*kmemset(char *s, int c, size_t n)
{
	size_t	i;
	char	*tmp;

	i = 0;
	tmp = (char *)s;
	while (i < n)
	{
		tmp[i] = c;
		i++;
	}
	return (s);
}