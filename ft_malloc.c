#include "malloc.h"

void createNewStdAlloc(size_t size, t_map *zone)
{

}

void *ft_malloc(size_t size)
{
	if (size <= 0 || !initZones())
		return (NULL);

	if (size <= )
		createNewStdAlloc(size, size <= TINY_ZONE ? zones->tiny : zones->small);
	return NULL;
}

int main()
{
	char *str = NULL;
	char *str2 = NULL;

	str = ft_malloc(10);
	str2 = ft_malloc(1);
//	if (str == NULL)
//		printf("NULL\n");

	return 0;
}