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

void 	*zoneParser(t_map *zone, size_t size)
{
	void 		*retNewStdAlloc;
	while (zone->next)
	{
		if (zone->availableSpace > size + HEAD_SIZE)
		{
			retNewStdAlloc = findAlloc(size, zone); // TODO : If findFreeAlloc doesnt find, pushback a new zone
			if (retNewStdAlloc)
				return retNewStdAlloc;
		}
		zone = zone->next;
	}
	if (!pushbackMem(0, zone->type, &zone))
		return NULL;
	else
		return (zoneParser(zone, size));
}