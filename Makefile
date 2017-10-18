ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc

FLAGS = -Werror -Wextra -Wall

PATH_SRC = src

PATH_OBJ = obj

PATH_INCLUDES = includes/

SRC = malloc.c \
	select_header.c \
	add_zone.c \
	free.c \
	realloc.c \
	calloc.c \
	show_alloc_mem.c \
	ft_bzero.c \
	ft_memcpy.c \
	ft_putchar.c

OBJ = $(SRC:%.c=obj/%.o)

all: $(NAME)

$(NAME): obj $(OBJ)
	$(CC) -shared -o $@ $(OBJ)
	ln -sf $(NAME) libft_malloc.so

$(PATH_OBJ)/%.o: $(PATH_SRC)/%.c
	$(CC) $(FLAGS) -fpic -o $@ -c $< -I includes

obj:
	mkdir -p obj/

clean:
		/bin/rm -f $(OBJ)

fclean: clean
		/bin/rm -f $(NAME) libft_malloc.so

re: clean fclean all
