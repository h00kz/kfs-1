#include "libk.h"

int	kstrncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*cast_s1;
	unsigned char	*cast_s2;

	i = 0;
	cast_s1 = (unsigned char *)s1;
	cast_s2 = (unsigned char *)s2;
	while (i < n && (cast_s1[i] || cast_s2[i]))
	{
		if (cast_s1[i] != cast_s2[i])
			return (cast_s1[i] - cast_s2[i]);
		i++;
	}
	return (0);
}