#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <stdlib.h>

#include <stdio.h>

# define TINY_ALLOC 1024
# define SMALL_ALLOC 1024 * 100
# define TINY_ZONE TINY_ALLOC * 100
# define SMALL_ZONE SMALL_ALLOC * 100
# define HEAD_SIZE sizeof(t_head)

enum zoneType
{
	TINY,
	SMALL,
	LARGE
};

typedef struct 		s_head
{
	size_t			size; // size of the alloc contained here
	size_t			spaceBeforeNext; // if at -1, there is no next
	void			*mem; // pointer returned to the user
	struct s_head	*next; // pointer to next header
}					t_head;

typedef struct 		s_map
{
	size_t			availableSpace; // space left in the zone, calculated at each alloc
	int				type; // type of the zone (enum zoneType)
	t_head			*firstHead; // pointer to the first alloc's header
	void			*mem; // pointer to the zone's memory
	struct s_map	*next; // pointer to the next zone 
}					t_map;

typedef struct 		s_zones
{
	t_map			*tiny;
	t_map			*small;
	t_map			*large;
}					t_zones;

t_zones 			*zones;

int					initZones();
int 				pushbackMem(int type, t_map **targetZone);
int					calculateSpaceLeft(t_map *zone);
t_map 				*zoneParser(t_map *zone, size_t size);
void 				*createNewStdAlloc(size_t size, t_map *zone);

#endif