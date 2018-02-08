#include "malloc.h"

void *ft_malloc(size_t size)
{
	if (size == 0 || !init_zones())
		return (NULL);
	printf("zones successfully created !\n");

	return NULL;
}

int main()
{
	ft_malloc(1);

	ft_malloc(2);

	return 0;
}