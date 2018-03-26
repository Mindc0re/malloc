#include "malloc.h"

int initZones()
{
	if (!zones)
	{
		zones = (t_zones *)mmap(0, sizeof(t_zones), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if (!zones)
			return 0;
		zones->tiny = NULL;
		zones->small = NULL;
		if (!pushbackMem(TINY, &zones->tiny))
		{
			printf("Failed tiny\n");
			return 0;
		}
		if (!pushbackMem(SMALL, &zones->small))
		{
			printf("Failed small\n");
			return 0;
		}
		printf("Zones successfully created !\n");
		return 1;
	}
	printf("\nZones already exist\n");
	return 1;
}

int pushbackMem(int type, t_map **targetZone)
{
//	t_map *tmp_l;
//	t_map *new;

//	new = NULL;
//	tmp_l = zone;
//	t_map *targetZone = type == TINY ? zones->tiny : zones->small;
	if (!(*targetZone))
	{
		printf("Creating new %s zone\n", type == TINY ? "TINY" : "SMALL");
		if (((*targetZone) = (t_map *)mmap(0, sizeof(t_map), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == (void *)-1)
			return (0);
		if (((*targetZone)->mem = mmap(0, type == TINY ? TINY_ZONE : SMALL_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == (void *)-1)
			return (0);
		(*targetZone)->availableSpace = type == TINY ? TINY_ZONE : SMALL_ZONE;
		(*targetZone)->type = type;
		(*targetZone)->firstHead = NULL;
		(*targetZone)->next = NULL;
	}
	else
	{
		// if (!(new = (t_map *)mmap(0, sizeof(t_map), PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)))
		// 	return (0);
		// new->next = NULL;
		// new->mem = mmap(0, TINY_ZONE, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		// while (tmp_l->next)
		// 	tmp_l = tmp_l->next;
		// new->prev = tmp_l;
		// tmp_l->next = new;
		printf("Pushback already done\n");
		return (0);
	}
	return (1);
}