#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <stdlib.h>

# include <stdio.h>

# define TINY_ALLOC 1024
# define SMALL_ALLOC 1024 * 100
# define TINY_ZONE TINY_ALLOC * 104
# define SMALL_ZONE SMALL_ALLOC * 104
# define HEAD_SIZE sizeof(t_head)

enum zoneType
{
	TINY,
	SMALL,
	LARGE
};

typedef struct 		s_head
{
	size_t			size;
	size_t			spaceBeforeNext;
	void			*mem;
	struct s_head	*next;
}					t_head;

typedef struct 		s_map
{
	size_t			availableSpace;
	int				type;
	t_head			*firstHead;
	void			*mem;
	struct s_map	*next;
}					t_map;

typedef struct 		s_zones
{
	t_map			*tiny;
	t_map			*small;
	t_map			*large;
}					t_zones;

t_zones 			*zones;

void 				*ft_malloc(size_t size);
void				show_alloc_mem();

int					initZones();
int 				pushbackMem(int type, t_map **targetZone);
int					calculateSpaceLeft(t_map *zone);
void 				*zoneParser(t_map *zone, size_t size);
void 				*createNewStdAlloc(size_t size, t_map *zone);

#endif