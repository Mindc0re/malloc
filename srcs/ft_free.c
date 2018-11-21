#include "malloc.h"

// Cette fonction unmap une zone si elle n'a plus lieu d'etre utilisee.
// C'est a dire : La zone n'a aucun block USED ; Il y a au moins une autre zone du meme type dans laquelle il reste PLUSIEURS blocks FREE
// Doit-elle unmap une zone si c'est la seule zone creee ? A voir.

// Trouver comment mettre à jour le spaceLeft de la zone dans laquelle on a free le block. Pas opti de reparcourir toutes les zones.
// On peut peut etre jouer avec les valeurs des adresses et déduire dans quelle zone se trouve ptr_head : "if (ptr_head) < zone + ZONE_LENGTH"
int			unmap_zone(t_map *zone, size_t map_size)
{
	t_map	*tmp;
	t_map	*tmp_next;
	int 	var_de_merde_pour_checker_si_on_free_le_premier_large = 0;

	tmp_next = NULL;
	if (!zone)
		return (0);
	if (zone->type == LARGE)
		tmp = g_zones.large;
	else
		tmp = zone->type == SMALL ? g_zones.small : g_zones.tiny;
	if (tmp == zone)
	{
		if (tmp->type == LARGE && tmp->next != NULL)
			tmp_next = tmp->next;
		else if (tmp->type != LARGE && tmp->next == NULL)
			return (0);
	}
	while (tmp->next != NULL && tmp->next != zone)
		tmp = tmp->next;
	tmp->next = zone->next;

	if (tmp == g_zones.large)
		var_de_merde_pour_checker_si_on_free_le_premier_large = 1;

	munmap(zone->mem, map_size);
	munmap(zone, sizeof(zone));

	if (var_de_merde_pour_checker_si_on_free_le_premier_large == 1)
		g_zones.large = NULL;

	if (tmp_next)
		g_zones.large = tmp_next;
	return (1);
}

void		optimize_free_blocks(t_head *ptr_head)
{
	t_head	*next;

	next = ptr_head->next;
	if (next && next->status == FREE)
	{
		ptr_head->size += next->size;
		ptr_head->spaceBeforeNext = next->spaceBeforeNext;
		ptr_head->next = next->next;
		optimize_free_blocks(ptr_head);
	}
}

int			verif_large_free(t_head *ptr_head)
{
	t_map	*tmp;

	tmp = g_zones.large;
	if (!tmp)
		return (0);
	while (tmp)
	{
		if (tmp->firstHead == ptr_head)
			return (unmap_zone(tmp, tmp->firstHead->size));
	}
	return (0);
}

// Ici, on va passer le block pointé en FREE si cela concerne une zone TINY ou SMALL.
// Pour une zone LARGE, on va unmap la zone directement.
// On doit egalement se charger d'optimiser les blocks FREE pour avoir les plus grands blocks possible disponibles.
// Doit-on remettre à 0 un block FREE ? Ou sa "mem" doit-elle pointer sur NULL ? A voir.
void		ft_free(void *ptr)
{
	t_head	*ptr_head;
	t_map	*z_ptr;
	
	if (!ptr)
		return ;
	ptr_head = ptr - HEAD_SIZE;
	ptr_head->status = FREE;
	if (!verif_large_free(ptr_head))
	{
		z_ptr = which_zone(ptr_head);
		if (!unmap_zone(z_ptr, z_ptr->type == SMALL ? SMALL_ZONE : TINY_ZONE))
			optimize_free_blocks(ptr_head);
	}
}