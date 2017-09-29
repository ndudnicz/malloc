#include <unistd.h>

void	ft_bzero(void *s, size_t n)
{
	char	*str;

	str = s;
	if (!n)
		return ;
	while (n > 0)
	{
		str[n - 1] = 0;
		n--;
	}
}
