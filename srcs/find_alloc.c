#include "malloc.h"


// Si on alloue une alloc plus petite que le block, il faut que FindFreeSpace
// puisse lier les maillons entre eux correctement.
// Ex. : On alloue 100 dans un FREE de 1000, donc quand on alloue juste derriere ce block (dans l'espace restant de 900),
// il faut que le next du block de 100 (ancien 1000)
// soit maintenant la nouvelle alloc qu'on vient de faire, et que le next de la nouvelle alloc soit l'ancien next du nouveau block de 100.
// A TESTER
t_head *findFreeBlock(size_t size, t_map *zone)
{
	t_head *tmp;

	tmp = zone->firstHead;
	while (tmp)
	{
		if (tmp->status == FREE && tmp->size >= size)
			break ;
		tmp = tmp->next;
	}
	if (tmp)
	{
		tmp->status = USED;
		tmp->size = size;
		tmp->spaceBeforeNext += tmp->size - size;
	}
	return (tmp);
}

t_head *findFreeSpace(size_t size, t_map *zone)
{
	t_head *tmp;
	t_head *new;

	tmp = zone->firstHead;
	while (tmp)
	{
		if (tmp->spaceBeforeNext >= size + HEAD_SIZE)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	new = tmp->mem + tmp->size;
	new->size = size;
	new->spaceBeforeNext = tmp->spaceBeforeNext - (HEAD_SIZE + size);
	new->status = USED;
	new->mem = tmp->mem + tmp->size + HEAD_SIZE;
	new->next = tmp->next ? tmp->next : NULL;
	tmp->next = new;
	tmp->spaceBeforeNext = 0;
	return (new);
}

t_head *initFirstHead(size_t size, t_map *zone)
{
	zone->firstHead = zone->mem;
	zone->firstHead->size = size;
	zone->firstHead->spaceBeforeNext = (zone->type == TINY ? TINY_ZONE : SMALL_ZONE) - HEAD_SIZE - size;
	zone->firstHead->status = USED;
	zone->firstHead->mem = zone->mem + HEAD_SIZE;
	zone->firstHead->next = NULL;
	return (zone->firstHead);
}

void *findAlloc(size_t size, t_map *zone)
{
	t_head	*new;

	if (size > zone->availableSpace)
		return (NULL);
	if (!zone->firstHead)
		new = initFirstHead(size, zone);
	else
	{
		new = findFreeBlock(size, zone);
		if (!new)
			new = findFreeSpace(size, zone);
	}
	zone->availableSpace = calculateSpaceLeft(zone);
	return (new ? new->mem : NULL);
}