#include "malloc.h"

static t_header	*ret_gt_next_header(t_header **next_available)
{
	t_header	*tmp;

	tmp = *next_available;
	if ((*next_available)->next && (*next_available)->next->taken)
		*next_available = NULL;
	else
		*next_available = (*next_available)->next;
	return (tmp);
}

static t_header	*get_next_header(size_t categorie, t_header *tmp)
{
	if (categorie == (size_t)TINY)
	{
		if (g_memory_lists.next_tiny_available &&
			g_memory_lists.next_tiny_available->taken == 0)
			return (ret_gt_next_header(&(g_memory_lists.next_tiny_available)));
		tmp = g_memory_lists.tiny;
	}
	else
	{
		if (g_memory_lists.next_small_available &&
			g_memory_lists.next_small_available->taken == 0)
			return (ret_gt_next_header(&(g_memory_lists.next_small_available)));
		tmp = g_memory_lists.small;
	}
	while (tmp)
	{
		if (tmp->taken == 0)
		{
			tmp->taken = 1;
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (tmp);
}

t_header		*select_header(size_t categorie)
{
	t_header	*header;

	header = get_next_header(categorie, NULL);
	if (!header)
	{
		if (add_new_zone(categorie, 0))
			return (NULL);
		else
			header = get_next_header(categorie, NULL);
	}
	return (header);
}
