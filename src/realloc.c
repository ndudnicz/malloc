#include "malloc.h"

static t_header	*parse(t_header **list, void *ptr)
{
	t_header	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->taken == 1 && tmp->mem == ptr)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

static t_header	*get_header(void *ptr)
{
	t_header	*tmp;

	tmp = NULL;
	if ((tmp = parse(&(g_memory_lists.tiny), ptr)))
		return (tmp);
	else if ((tmp = parse(&(g_memory_lists.small), ptr)))
		return (tmp);
	else if ((tmp = parse(&(g_memory_lists.large), ptr)))
		return (tmp);
	else
		return (tmp);
}

void			*realloc(void *ptr, size_t size)
{
	t_header	*header;
	void		*new;

	if (!ptr)
		return (malloc(size));
	if (!(header = get_header(ptr)))
		return (NULL);
	else
	{
		if (size <= header->size)
			return (ptr);
		if (!(new = malloc(size)))
			return (NULL);
		ft_memcpy(new, ptr, size);
		free(header->mem);
		return (new);
	}
}
