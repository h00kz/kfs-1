#include "libk.h"

static size_t	space(const char *str, size_t i)
{
	if (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		return (1);
	else
		return (0);
}

static size_t	isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

int64_t	katoi(const char *str)
{
	size_t  i = 0;
	size_t	j = 0;
	size_t	sign = 1;
	int64_t 	nb = 0;

	while (space(str, i))
		i++;
	if (str[i] == '-')
		sign *= -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
    while (isdigit(str[i + j]))
	{
		nb = nb * 10 + str[i + j] - '0';
		j++;
	}
	if (j > 10 && sign == -1)
		return (0);
	else if (j > 10)
		return (-1);
	return (nb * sign);
}