#include "malloc.h"

int		calculateSpaceLeft(t_map *zone)
{
	t_head	*tmp;
	int 	headCount;
	int 	totalSize;
	int		zoneSize;

	headCount = 0;
	totalSize = 0;
	zoneSize = zone->type == TINY ? TINY_ZONE : SMALL_ZONE;
	tmp = zone->firstHead;
	while (tmp)
	{
		headCount++;
		totalSize += tmp->size;
		tmp = tmp->next;
	}

	return (zoneSize - (headCount * HEAD_SIZE) - totalSize);
}