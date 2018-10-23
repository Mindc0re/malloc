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

int allocMem(int type, t_map **toAlloc)
{
	if (((*toAlloc) = (t_map *)mmap(0, sizeof(t_map), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == (void *)-1)
		return (0);
	if (((*toAlloc)->mem = mmap(0, type == TINY ? TINY_ZONE : SMALL_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == (void *)-1)
		return (0);
	(*toAlloc)->availableSpace = type == TINY ? TINY_ZONE : SMALL_ZONE;
	(*toAlloc)->type = type;
	(*toAlloc)->firstHead = NULL;
	(*toAlloc)->next = NULL;
	return (1);
}

int pushbackMem(int type, t_map **targetZone)
{
	t_map *tmp;
	t_map *new;

	if (!(*targetZone))
	{
		if (!allocMem(type, targetZone))
			return (0);
	}
	else
	{
		tmp = (*targetZone);
		while (tmp->next)
			tmp = tmp->next;
		if (!allocMem(type, &new))
			return (0);
		tmp->next = new;
	}
	return (1);
}
