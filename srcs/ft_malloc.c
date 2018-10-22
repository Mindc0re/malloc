#include "malloc.h"

void *createNewStdAlloc(size_t size, t_map *zone)
{
	t_head	*tmp;
	t_head	*new;

	if (!zone->firstHead)
	{
		zone->firstHead = zone->mem;
		zone->firstHead->size = size;
		zone->firstHead->spaceBeforeNext = (zone->type == TINY ? TINY_ZONE : SMALL_ZONE) - HEAD_SIZE - size;
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

	zone = size <= TINY_ALLOC ? zones->tiny : zones->small;
	alloc = NULL;
	if (size <= SMALL_ALLOC)
		alloc = zoneParser(zone, size);
	return alloc;
}
