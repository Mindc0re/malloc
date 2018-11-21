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
	t_map		*tmp;

	tmp = zone;
	while (tmp)
	{
		if (tmp->availableSpace > size + HEAD_SIZE)
		{
			retNewStdAlloc = findAlloc(size, tmp);
			if (retNewStdAlloc)
				return retNewStdAlloc;
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (!pushbackMem(0, tmp->type, &tmp))
		return NULL;
	else
		return (zoneParser(tmp, size));
}