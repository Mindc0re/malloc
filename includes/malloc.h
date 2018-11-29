#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <sys/mman.h>
# include <stdlib.h>
# include <pthread.h>

# include <stdio.h>

# define TINY_ALLOC (size_t)getpagesize() / 4
# define SMALL_ALLOC TINY_ALLOC * 20
# define TINY_ZONE TINY_ALLOC * 104
# define SMALL_ZONE SMALL_ALLOC * 104
# define HEAD_SIZE sizeof(t_head)

enum 				e_zoneType
{
	TINY,
	SMALL,
	LARGE
};

enum 				e_status
{
	FREE,
	USED
};

typedef struct 		s_head
{
	size_t			size;
	size_t			spaceBeforeNext;
	int				status;
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

t_zones				g_zones;
pthread_mutex_t		g_mutex;

void 				*malloc(size_t size);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem();

int					initZones(void);
void				*allocLargeZone(size_t size);
int 				pushbackMem(size_t size, int type, t_map **targetZone);
int					calculateSpaceLeft(t_map *zone);
void 				*zoneParser(t_map *zone, size_t size);
void 				*findAlloc(size_t size, t_map *zone);
t_map				*which_zone(t_head *ptr_head);

void				*ft_memcpy(void *dst, void *src, size_t n);


#endif