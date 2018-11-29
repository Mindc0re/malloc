#include "malloc.h"

// TODO : Checker getrlimit() pour limiter l'appel a malloc si trop de memoire a ete allouee
void	*malloc(size_t size)
{
	void 		*alloc;

	pthread_mutex_lock(&g_mutex);
	if (size <= 0)
		return (NULL);
	alloc = NULL;
	if (size > SMALL_ALLOC)
		return allocLargeZone(size);
	else if (size > TINY_ALLOC)
	{
		if (!g_zones.small)
			pushbackMem(0, SMALL, &g_zones.small);
		alloc = zoneParser(g_zones.small, size);
	}
	else if (size <= TINY_ALLOC)
	{
		if (!g_zones.tiny)
			pushbackMem(0, TINY, &g_zones.tiny);
		alloc = zoneParser(g_zones.tiny, size);
	}
	pthread_mutex_unlock(&g_mutex);
	return alloc;
}
