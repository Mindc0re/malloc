#include "malloc.h"

int init_zones()
{
	if (!zones)
	{
		printf("NO ZONE !\n");
		zones = (t_prealloc *)mmap(0, sizeof(t_prealloc), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if (!pushback_mem(zones->tiny))
		{
			printf("failed tiny\n");
			return 0;
		}
		if (!pushback_mem(zones->small))
		{
			printf("failed small\n");
			return 0;
		}
		return 1;
	}
	return 1;
}

int pushback_mem(t_mem *zone)
{
	t_mem *tmp_l;
	t_mem *new;

	new = NULL;
	tmp_l = zone;
	if (!zone)
	{
		if (!(zone = (t_mem *)mmap(0, sizeof(t_mem), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)))
			return 0;
		zone->prev = NULL;
		zone->next = NULL;
		zone->mem = mmap(0, TINY_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	}
	else
	{
		if (!(new = (t_mem *)mmap(0, sizeof(t_mem), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)))
			return 0;
		new->next = NULL;
		new->mem = mmap(0, TINY_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		while (tmp_l->next)
			tmp_l = tmp_l->next;
		new->prev = tmp_l;
		tmp_l->next = new;
	}
	return 1;
}