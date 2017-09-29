#include "malloc.h"
#include <stdio.h>

static void		print_list(t_header **list)
{
	t_header	*tmp;
	char		*format;
	long int	p;

	tmp = *list;
	format = "%p - %p : %d octets\n";
	while (tmp)
	{
		if (tmp->taken == 1)
		{
			p = (long int)tmp->mem;
			printf(format, p, p + tmp->size, tmp->size);
		}
		tmp = tmp->next;
	}
}

void			show_alloc_mem(void)
{
	if (g_memory_lists.tiny)
	{
		printf("TINY : %p\n", g_memory_lists.tiny);
		print_list(&(g_memory_lists.tiny));
	}
	if (g_memory_lists.small)
	{
		printf("SMALL : %p\n", g_memory_lists.small);
		print_list(&(g_memory_lists.small));
	}
	if (g_memory_lists.large)
	{
		printf("LARGE : %p\n", g_memory_lists.large);
		print_list(&(g_memory_lists.large));
	}
}

static void		print_memory(void *mem, size_t len)
{
	size_t		i;
	char		*tmp;

	i = 0;
	tmp = (char*)mem;
	while (i < len)
	{
		printf("%08x ", tmp[i]);
		i++;
		if (i < len && !(i % 8))
			ft_putchar('\n');
	}
	ft_putchar('\n');
	ft_putchar('\n');
}

static void		print_list_hex(t_header **list)
{
	t_header	*tmp;
	char		*format;
	long int	p;

	tmp = *list;
	format = "%p - %p : %d octets\n";
	while (tmp)
	{
		if (tmp->taken == 1)
		{
			p = (long int)tmp->mem;
			printf(format, p, p + tmp->size, tmp->size);
			print_memory(tmp->mem, tmp->size);
		}
		tmp = tmp->next;
	}
}

void			show_alloc_mem_hex(void)
{
	if (g_memory_lists.tiny)
	{
		printf("TINY : %p\n", g_memory_lists.tiny);
		print_list_hex(&(g_memory_lists.tiny));
	}
	if (g_memory_lists.small)
	{
		printf("SMALL : %p\n", g_memory_lists.small);
		print_list_hex(&(g_memory_lists.small));
	}
	if (g_memory_lists.large)
	{
		printf("LARGE : %p\n", g_memory_lists.large);
		print_list_hex(&(g_memory_lists.large));
	}
}
