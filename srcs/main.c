#include "malloc.h"

int main(void)
{
	char *str = ft_malloc(10);

	ft_free(str);

	(void)str;

	show_alloc_mem();

	return 0;
}