#include <unistd.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*new_dst;
	char	*new_src;

	if (!n || dst == src)
		return (dst);
	new_dst = (char*)dst;
	new_src = (char*)src;
	while (--n)
	{
		*new_dst++ = *new_src++;
	}
	*new_dst = *new_src;
	return (dst);
}
