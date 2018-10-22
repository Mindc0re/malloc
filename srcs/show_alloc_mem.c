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

void	show_alloc_mem()
{
	t_head *tmp;
	int total;

	tmp = NULL;
	total = 0;
	if (!zones)
		return ;
	tmp = zones->tiny ? zones->tiny->firstHead : NULL;
	if (tmp)
		total += print_mem(tmp, "TINY");

	tmp = zones->small ? zones->small->firstHead : NULL;
	if (tmp)
		total += print_mem(tmp, "SMALL");

	tmp = zones->large ? zones->large->firstHead : NULL;
	if (tmp)
		total += print_mem(tmp, "LARGE");

	printf("Total : %d octets\n", total);
}
