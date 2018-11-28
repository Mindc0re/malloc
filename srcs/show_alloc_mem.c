#include "malloc.h"

int		print_mem(t_map *tmp, char *type)
{
	int 	total;
	t_head *tmp_head;

	total = 0;
	while (tmp)
	{
		tmp_head = tmp->firstHead;
		printf("\n%s : %p\n", type, tmp);
		while (tmp_head)
		{
			if (tmp_head->status == USED)
			{
				printf("%p - %p : %zu octets\n", tmp_head->mem, tmp_head->mem + tmp_head->size - 1, tmp_head->size);
				total += tmp_head->size;
			}
			tmp_head = tmp_head->next;
		}
		tmp = tmp->next;
	}
	return total;
}

// Parcourir toutes les zones (si plusieurs zones du meme type allouees)
void	show_alloc_mem()
{
	t_map *tmp;
	int total;

	tmp = NULL;
	total = 0;
	tmp = g_zones.tiny;
	if (tmp)
		total += print_mem(tmp, "TINY");
	tmp = g_zones.small;
	if (tmp)
		total += print_mem(tmp, "SMALL");

	tmp = g_zones.large;
	if (tmp)
		total += print_mem(tmp, "LARGE");

	printf("Total : %d octets\n\n", total);
}
