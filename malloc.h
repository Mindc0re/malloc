#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <stdlib.h>

#include <stdio.h>

# define TINY_ZONE 1024 * 100
# define SMALL_ZONE TINY_ZONE * 100

enum zoneType
{
	TINY,
	SMALL,
	LARGE
}

typedef struct 		s_head
{
	size_t			size;
	size_t			spaceBeforeNext;
	void			*mem;
	struct s_mem	*next;
}					t_head;

typedef struct 		s_map
{
	size_t			available_space;
	zoneType		type;
	s_head			*next;
}					t_map;

typedef struct 		s_zones
{
	t_map			tiny;
	t_map			small;
	t_map			large;
}					t_zones;

t_zones 			*zones;

int					init_zones();
int 				pushback_mem(t_mem *zone);


#endif