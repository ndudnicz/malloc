#include "malloc.h"

void	*malloc(size_t size)
{
	t_header	*ptr;

	if (size <= (size_t)TINY)
		ptr = select_header(TINY);
	else if (size <= (size_t)SMALL)
		ptr = select_header(SMALL);
	else
	{
		size = ((size / PAGE_SIZE) + 1) * PAGE_SIZE;
		ptr = add_new_large_zone(size);
	}
	if (ptr)
	{
		ptr->taken = 1;
		ptr->size = size;
	}
	return (ptr ? ptr->mem : NULL);
}
