#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>

# define PAGE_SIZE		(getpagesize())
# define MMAP_PROT		(PROT_READ | PROT_WRITE)
# define MMAP_FLAGS		(MAP_ANON | MAP_PRIVATE)
# define TINY			(PAGE_SIZE)
# define SMALL			(PAGE_SIZE * 128)
# define ZONE_SIZE		(PAGE_SIZE / 32)
# define GET_CAT(x)		(x <= (size_t)TINY ? TINY : SMALL)

typedef struct	s_header
{
	size_t			size;
	int				taken;
	void			*mem;
	struct s_header	*next;
}				t_header;

typedef struct	s_memory_lists
{
	struct s_header		*tiny;
	struct s_header		*last_tiny;
	struct s_header		*next_tiny_available;
	struct s_header		*small;
	struct s_header		*last_small;
	struct s_header		*next_small_available;
	struct s_header		*large;
	struct s_header		*last_large;
}				t_memory_lists;

t_memory_lists	g_memory_lists;

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			show_alloc_mem(void);
void			*calloc(size_t count, size_t size);
void			show_alloc_mem_hex(void);

/*
** TINY / SMALL HANDLING
*/

t_header		*select_header(size_t categorie);
int				add_new_zone(size_t categorie, int i);

/*
** LARGE HANDLING
*/

t_header		*add_new_large_zone(size_t size);

/*
** LIBFT
*/

void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			ft_putchar(char c);

#endif
