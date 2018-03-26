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

// May change t_map *zone type to it's address
t_map 	*zoneParser(t_map *zone, size_t size)
{
	void 		*retNewStdAlloc;
	while (zone->next)
	{
		if (zone->availableSpace > size + HEAD_SIZE)
		{
			retNewStdAlloc = createNewStdAlloc(size, zone);
			if (retNewStdAlloc)
				return retNewStdAlloc;
		}
		zone = zone->next;
	}
	if (!pushbackMem(zone->type, &zone))
	{
		printf("pushbackMem failed !");
		return NULL;
	}
	else
		return (zoneParser(zone, size));
}