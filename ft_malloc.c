#include "malloc.h"

void *ft_malloc(size_t size)
{
	if (size <= 0 || !init_zones())
		return (NULL);

	t_head *head = mmap(0, sizeof(t_head), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (!head)
		return NULL;
	head->size = size;

	void *mem = mmap(head + sizeof(t_head), size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (mem == (void *) -1)
		return NULL;

	printf("Head address = %p\n", head);
	printf("Mem address in malloc = %p\n", mem);
	printf("size stocked in malloc : %d\n", (int)head->size);

	return mem;
}

int main()
{
	char *str = NULL;

	str = ft_malloc(10);
	if (str == NULL)
		printf("NULL\n");

	return 0;
}