#include "malloc.h"

int main(void)
{
	int i = 0;

	char *str = ft_malloc(5);
	for (i = 0 ; i < 4 ; i++)
		str[i] = 'a';
	str[i] = '\0';

	char *str2 = ft_malloc(5);
	for (i = 0 ; i < 4 ; i++)
		str2[i] = 'a';
	str2[i] = '\0';

	char *str3 = ft_malloc(5);
	for (i = 0 ; i < 4 ; i++)
		str3[i] = 'a';
	str3[i] = '\0';

	char *str4 = ft_malloc(5);
	for (i = 0 ; i < 4 ; i++)
		str4[i] = 'a';
	str4[i] = '\0';

	show_alloc_mem();

	ft_free(str3);
	printf("%s\n%s\n%s\n%s\n\n", str, str2, str3, str4);
	show_alloc_mem();

	str2 = ft_realloc(str2, 5);
	for (i = 0 ; i < 2 ; i++)
		str2[i] = 'a';
	str2[i] = '\0';
	printf("%s\n%s\n%s\n%s\n\n", str, str2, str3, str4);
	show_alloc_mem();

	// char *str = ft_malloc(SMALL_ALLOC + 1);
	// str[0] = 'a';
	// str[1] = '\0';
	// printf("str = %s\n", str);
	// show_alloc_mem();

	// ft_free(str);
	// show_alloc_mem();

	// char *str2 = ft_malloc(SMALL_ALLOC + 1);
	// str2[0] = 'b';
	// str2[1] = '\0';
	// printf("str2 = %s\n", str2);
	// show_alloc_mem();

	// ft_free(str2);
	// show_alloc_mem();

	return 0;
}