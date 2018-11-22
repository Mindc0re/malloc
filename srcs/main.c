#include "malloc.h"

int main(void)
{
	char *str = ft_malloc(SMALL_ALLOC + 1);
	str[0] = 'a';
	str[1] = '\0';
	printf("str = %s\n", str);
	show_alloc_mem();

	ft_free(str);
	show_alloc_mem();

	char *str2 = ft_malloc(SMALL_ALLOC + 1);
	str2[0] = 'b';
	str2[1] = '\0';
	printf("str2 = %s\n", str2);
	show_alloc_mem();

	// ft_free(str2);
	// show_alloc_mem();

	return 0;
}