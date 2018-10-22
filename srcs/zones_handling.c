#include "malloc.h"

int initZones()
{
	if (!zones)
	{
		zones = (t_zones *)mmap(0, sizeof(t_zones), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if (!zones)
			return 0;
		zones->tiny = NULL;
		zones->small = NULL;
		if (!pushbackMem(TINY, &zones->tiny))
			return 0;
		if (!pushbackMem(SMALL, &zones->small))
			return 0;
		return 1;
	}
	return 1;
}

int pushbackMem(int type, t_map **targetZone)
{
	t_map *tmp;
	t_map *new;

	tmp = NULL;
	if (!(*targetZone))
		new = *targetZone;
	else
	{
		tmp = *targetZone;
		while (tmp->next)
			tmp = tmp->next;
	}
	if ((new = (t_map *)mmap(0, sizeof(t_map), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == (void *)-1)
		return (0);
	if ((new->mem = mmap(0, type == TINY ? TINY_ZONE : SMALL_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == (void *)-1)
		return (0);	
	new->availableSpace = type == TINY ? TINY_ZONE : SMALL_ZONE;
	new->type = type;
	new->firstHead = NULL;
	new->next = NULL;
	if (tmp)
		tmp->next = new;

	return (1);
}