#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/mman.h>

#include <stdio.h>

# define TINY_ZONE 4096 * 100
# define SMALL_ZONE 4096 * 2 * 100

typedef struct 		s_mem
{
	struct s_mem	*prev;
	void			*mem;
	struct s_mem	*next;
}					t_mem;

typedef struct 		s_prealloc
{
	t_mem			*tiny;
	t_mem			*small;
}					t_prealloc;

t_prealloc 			*zones;

int					init_zones();
int 				pushback_mem(t_mem *zone);


#endif