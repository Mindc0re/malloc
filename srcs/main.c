#include "../includes/malloc.h"

int main()
{
	// int totalMemoryDistributed = 0;
	// int nAlloc = 0;
	// char *str = NULL;
	char *str2 = NULL;
	char *str3 = NULL;
	char *str4 = NULL;

	show_alloc_mem();

	// while (totalMemoryDistributed <= TINY_ZONE)
	// {
	// 	str = ft_malloc(TINY_ALLOC);
	// 	// str[0] = 'c';
	// 	// printf("str address : %p\n", str);
	// 	// printf("str[0] = %c\n", str[0]);

	// 	totalMemoryDistributed += (TINY_ALLOC + HEAD_SIZE);
	// 	nAlloc++;
	// }

	// printf("\n\nAllocated %d times\n", nAlloc);

	str2 = ft_malloc(4);
	str2[0] = 's';
	str2[1] = 't';
	str2[2] = 'r';
	str2[3] = '\0';
	// printf("str2 = %s\n", str2);
	show_alloc_mem();
	printf("\n");

	str3 = ft_malloc(10);
	str3[0] = '1';
	str3[1] = '2';
	str3[2] = '3';
	str3[3] = '\0';
	// printf("str3 = %s\n", str3);
	show_alloc_mem();
	printf("\n");

	str4 = ft_malloc(SMALL_ALLOC + 1);
	str4 = ft_malloc(SMALL_ALLOC + 1);
	str4[0] = 'h';
	str4[1] = '\0';
	show_alloc_mem();
	printf("\n");	

	return 0;
}