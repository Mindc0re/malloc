#include "malloc.h"

// TODO : Checker getrlimit() pour limiter l'appel a malloc si trop de memoire a ete allouee
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
