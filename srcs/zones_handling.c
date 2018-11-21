#include "malloc.h"

void	*allocLargeZone(size_t size)
{
	t_map *tmp;

	if (!pushbackMem(size, LARGE, &g_zones.large))
		return (0);
	tmp = g_zones.large;
	while (tmp->next)
		tmp = tmp->next;
	tmp->firstHead = tmp->mem;
	tmp->firstHead->size = size;
	tmp->firstHead->spaceBeforeNext = 0;
	tmp->firstHead->status = USED;
	tmp->firstHead->mem = tmp->mem + HEAD_SIZE;
	tmp->firstHead->next = NULL;
	return (tmp->firstHead->mem);
}

int 	allocMem(size_t size, int type, t_map **toAlloc)
{
	if (((*toAlloc) = (t_map *)mmap(0, sizeof(t_map), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == (void *)-1)
		return (0);
	if (((*toAlloc)->mem = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == (void *)-1)
		return (0);
	(*toAlloc)->availableSpace = type == LARGE ? 0 : size;
	(*toAlloc)->type = type;
	(*toAlloc)->firstHead = NULL;
	(*toAlloc)->next = NULL;
	return (1);
}

int 	pushbackMem(size_t size, int type, t_map **targetZone)
{
	t_map 	*tmp;
	t_map 	*new;

	if (type == LARGE)
		size += HEAD_SIZE;
	else
		size = type == TINY ? TINY_ZONE : SMALL_ZONE;
	if (!targetZone || !(*targetZone))
	{
		if (!allocMem(size, type, targetZone))
			return (0);
	}
	else
	{
		tmp = (*targetZone);
		while (tmp->next)
			tmp = tmp->next;
		if (!allocMem(size, type, &new))
			return (0);
		tmp->next = new;
	}
	return (1);
}
