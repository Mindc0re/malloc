#include "../includes/malloc.h"

int main()
{
	int totalMemoryDistributed = 0;
	int nAlloc = 0;
	char *str = NULL;

	show_alloc_mem();

	while (totalMemoryDistributed <= TINY_ZONE)
	{
		str = ft_malloc(TINY_ALLOC);
		totalMemoryDistributed += (TINY_ALLOC + HEAD_SIZE);
		nAlloc++;
	}

	printf("\n\nAllocated %d times\n", nAlloc);

	show_alloc_mem();

	str = ft_malloc(TINY_ALLOC);

	show_alloc_mem();

	(void)str;

	return 0;
}
