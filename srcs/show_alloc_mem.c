#include "malloc.h"

int		print_mem(t_head *tmp, char *type)
{
	int total;

	total = 0;
	printf("%s : %p\n", type, tmp);
	while (tmp)
	{
		printf("%p - %p : %zu octets\n", tmp->mem, tmp->mem + tmp->size, tmp->size);
		total += tmp->size;
		tmp = tmp->next;
	}
	return total;
}

// Parcourir toutes les zones (si plusieurs zones du meme type allouee)
void	show_alloc_mem()
{
	t_head *tmp;
	int total;

	tmp = NULL;
	total = 0;
	tmp = g_zones.tiny ? g_zones.tiny->firstHead : NULL;
	if (tmp)
		total += print_mem(tmp, "TINY");

	tmp = g_zones.small ? g_zones.small->firstHead : NULL;
	if (tmp)
		total += print_mem(tmp, "SMALL");

	tmp = g_zones.large ? g_zones.large->firstHead : NULL;
	if (tmp)
		total += print_mem(tmp, "LARGE");

	printf("Total : %d octets\n", total);
}
