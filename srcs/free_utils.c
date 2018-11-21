#include "malloc.h"

// t_map 	*is_large(t_map *zone, t_head *ptr_head)
// {
// 	while (zone)
// 	{
// 		if (zone->firstHead == ptr_head)
// 			break ;
// 		zone = zone->next;
// 	}
// 	return (zone);
// }

// // if (ptr_head) < zone + ZONE_LENGTH

t_map	*is_tiny_or_small(t_map *zone, t_head *ptr_head)
{
	int size;

	size = zone->type == SMALL ? SMALL_ZONE : TINY_ZONE;
	while (zone)
	{
		if ((void *)ptr_head < (void *)((void *)zone->mem + size))
			break ;
		zone = zone->next;
	}
	return (zone);
}

t_map	*which_zone(t_head *ptr_head)
{
	t_map	*tmp;
	t_map	*ret;

	if (!ptr_head)
		return (NULL);
	// tmp = g_zones.large;
	// if ((ret = is_large(tmp, ptr_head)) != NULL)
	// 	return (ret);
	tmp = g_zones.small;
	if (tmp && (ret = is_tiny_or_small(tmp, ptr_head)) != NULL)
		return (ret);
	tmp = g_zones.tiny;
	if (tmp && (ret = is_tiny_or_small(tmp, ptr_head)) != NULL)
		return (ret);
	return (NULL);
}