#include "malloc.h"
#include <sys/mman.h>

static void		init_header(t_header *new_header, void **new_zone)
{
	new_header->size = 0;
	new_header->taken = 0;
	new_header->mem = *new_zone;
	new_header->next = NULL;
}

static void		push(t_header **begin, t_header **new, t_header **last)
{
	t_header	*tmp;

	tmp = *begin;
	if (!tmp)
	{
		*begin = *new;
		*last = *new;
	}
	else
	{
		(*last)->next = *new;
		(*last) = *new;
	}
}

static void		init_and_push(size_t cat, void **new_header, void **new_zone,
		int i)
{
	init_header(*new_header, new_zone);
	if (cat == (size_t)TINY)
	{
		push(&(g_memory_lists.tiny), (t_header**)new_header,
			&(g_memory_lists.last_tiny));
		if (!g_memory_lists.next_tiny_available || i == 0)
			g_memory_lists.next_tiny_available = (t_header*)(*new_header);
	}
	else if (cat == (size_t)SMALL)
	{
		push(&(g_memory_lists.small), (t_header**)new_header,
			&(g_memory_lists.last_small));
		if (!g_memory_lists.next_small_available || i == 0)
			g_memory_lists.next_small_available = (t_header*)(*new_header);
	}
	else
		push(&(g_memory_lists.large),
		(t_header**)new_header, &(g_memory_lists.last_large));
}

int				add_new_zone(size_t categorie, int i)
{
	void		*new_header;
	void		*tmp_header;
	void		*new_zone;
	void		*tmp_zone;

	if (!(new_header = (void*)mmap(0,
		(sizeof(t_header) * ZONE_SIZE), MMAP_PROT, MMAP_FLAGS, -1, 0)))
		return (-1);
	if (!(new_zone = (void*)mmap(0,
		GET_CAT(categorie) * ZONE_SIZE, MMAP_PROT, MMAP_FLAGS, -1, 0)))
		return (-1);
	while (i < ZONE_SIZE)
	{
		tmp_header = new_header + (sizeof(t_header) * i);
		tmp_zone = new_zone + (GET_CAT(categorie) * i);
		init_and_push(categorie, &tmp_header, &tmp_zone, i);
		i++;
		tmp_header = NULL;
		tmp_zone = NULL;
	}
	return (0);
}

t_header		*add_new_large_zone(size_t size)
{
	void		*new_header;
	void		*new_zone;

	if (!(new_header = (void*)mmap(0,
		sizeof(t_header), MMAP_PROT, MMAP_FLAGS, -1, 0)))
		return (NULL);
	if (!(new_zone = (void*)mmap(0, size, MMAP_PROT, MMAP_FLAGS, -1, 0)))
		return (NULL);
	init_and_push(size, &new_header, &new_zone, 0);
	return (new_header);
}
