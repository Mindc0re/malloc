#include "malloc.h"

void *createNewStdAlloc(size_t size, t_map *zone)
{
	t_head	*tmp;
	t_head	*new;

	printf("This is a %s zone\n", zone->type == TINY ? "TINY" : "SMALL");
	if (!zone->firstHead)
	{
		zone->firstHead = zone->mem;
		zone->firstHead->size = size;
		zone->firstHead->spaceBeforeNext = (zone->type == TINY ? TINY_ZONE : SMALL_ZONE) - HEAD_SIZE - size;
		zone->firstHead->mem = zone->firstHead + sizeof(t_head);
		zone->firstHead->next = NULL;
		new = zone->firstHead;
	}
	else
	{
		tmp = zone->firstHead;
		while (tmp->next)
		{
			if (tmp->spaceBeforeNext > size + HEAD_SIZE)
				break ;
			tmp = tmp->next;
		}
		new = tmp->mem + tmp->size;
		new->size = size;
		new->spaceBeforeNext = tmp->next ? ((void *)tmp->next - (tmp->mem + tmp->size)) - (HEAD_SIZE + size) : (tmp->spaceBeforeNext - (HEAD_SIZE + size));
   		new->mem = new + sizeof(t_head);
		new->next = tmp->next ? tmp->next : NULL;
		tmp->next = new;
		tmp->spaceBeforeNext = 0;
	}
	printf("size left in new = %zu\n", new->spaceBeforeNext);
	zone->availableSpace = calculateSpaceLeft(zone);
//	printf("Available space left in zone = %zu\n", zone->availableSpace);

	printf("Header address : %p\n", new);
	printf("Alloc address : %p\n", new->mem);
	// printf("size left in new = %zu\n", new->spaceBeforeNext);
	return new->mem;
}

void *ft_malloc(size_t size)
{
	if (size <= 0 || !initZones())
		return (NULL);

	if (size <= SMALL_ALLOC)
		return createNewStdAlloc(size, size <= TINY_ALLOC ? zones->tiny : zones->small);
	return NULL;
}

int main()
{
	char *str = NULL;
	char *str2 = NULL;
	char *str3 = NULL;

	str = ft_malloc(10);
	str[0] = 'c';
	printf("str address : %p\n", str);
	printf("str[0] = %c\n", str[0]);

	str2 = ft_malloc(1025);
	str2[0] = 's';
	printf("str2 address : %p\n", str2);
	printf("str2[0] = %c\n", str2[0]);

	str3 = ft_malloc(10);
	str3[0] = 's';
	printf("str3 address : %p\n", str3);
	printf("str3[0] = %c\n", str3[0]);
	return 0;
}