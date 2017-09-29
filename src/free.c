#include <sys/mman.h>
#include "malloc.h"

static int		set_as_free(t_header **list, void *ptr,
		t_header **next_available)
{
	t_header	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (tmp->mem == ptr && tmp->taken == 1)
		{
			tmp->taken = 0;
			*next_available = tmp;
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static void		delete_large_header(t_header **prev,
		t_header **current, t_header **next)
{
	if (!*prev)
		g_memory_lists.large = *next;
	else
		(*prev)->next = *next;
	munmap((*current)->mem, (*current)->size);
	munmap(*current, sizeof(t_header));
}

static void		set_as_free_large(t_header **list, void *ptr)
{
	t_header	*tmp;
	t_header	*prev;

	tmp = *list;
	prev = NULL;
	while (tmp)
	{
		if (tmp->mem == ptr && tmp->taken == 1)
		{
			delete_large_header(&prev, &tmp, &(tmp->next));
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
	return ;
}

void			free(void *ptr)
{
	if (set_as_free(&(g_memory_lists.tiny), ptr,
		&(g_memory_lists.next_tiny_available)))
		return ;
	else if (set_as_free(&(g_memory_lists.small), ptr,
		&(g_memory_lists.next_small_available)))
		return ;
	else
		set_as_free_large(&(g_memory_lists.large), ptr);
	return ;
}
