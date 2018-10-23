#include "malloc.h"

// void splitHeadOnNewAlloc(t_head *newlyAllocated)
// {

// }


// TODO : Optimiser ca pour que ca trouve une alloc FREE
// TODO : Il faut aussi etre sur que le tmp dans le else peut bien contenir l'alloc demandee
// TODO : Coder la fonction au dessus
void *findFreeAlloc(size_t size, t_map *zone)
{
	t_head	*tmp;
	t_head	*new;

	if (!zone->firstHead)
	{
		zone->firstHead = zone->mem;
		zone->firstHead->size = size;
		zone->firstHead->spaceBeforeNext = (zone->type == TINY ? TINY_ZONE : SMALL_ZONE) - HEAD_SIZE - size;
		zone->firstHead->status = USED;
		zone->firstHead->mem = zone->mem + HEAD_SIZE;
		zone->firstHead->next = NULL;
		new = zone->firstHead;
	}
	else
	{
		tmp = zone->firstHead;
		while (tmp->next)
		{
			if (tmp->spaceBeforeNext > size + HEAD_SIZE)
				break ;
			tmp = tmp->next;
		}
		new = tmp->mem + tmp->size;
		new->size = size;
		new->spaceBeforeNext = tmp->spaceBeforeNext - (HEAD_SIZE + size);
		new->status = USED;
   		new->mem = tmp->mem + tmp->size + HEAD_SIZE;
		new->next = tmp->next ? tmp->next : NULL;
		tmp->next = new;
		tmp->spaceBeforeNext = 0;
	}
	zone->availableSpace = calculateSpaceLeft(zone);
	return new->mem;
}

void *ft_malloc(size_t size)
{
	void 		*alloc;
	t_map 		*zone;

	if (size <= 0 || !initZones())
		return (NULL);
	if (size > SMALL_ALLOC)
		return allocLargeZone(size);
	zone = size <= TINY_ALLOC ? g_zones->tiny : g_zones->small;
	alloc = NULL;
	if (size <= SMALL_ALLOC)
		alloc = zoneParser(zone, size);
	return alloc;
}
