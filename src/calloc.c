#include "malloc.h"

void	*calloc(size_t count, size_t size)
{
	void	*mem;
	size_t	new_size;

	new_size = count * size;
	mem = malloc(new_size);
	if (mem)
	{
		if (new_size <= (size_t)TINY)
			new_size = (size_t)TINY;
		else if (new_size <= (size_t)SMALL)
			new_size = (size_t)SMALL;
		else
			new_size = ((new_size / PAGE_SIZE) + 1) * PAGE_SIZE;
		ft_bzero(mem, new_size);
	}
	return (mem);
}
