#include "malloc.h"

// Cette fonction unmap une zone si elle n'a plus lieu d'etre utilisee.
// C'est a dire : La zone n'a aucun block USED ; Il y a au moins une autre zone du meme type dans laquelle il reste PLUSIEURS zones FREE
// Doit-elle unmap une zone si c'est la seule zone creee ? A voir.
// Trouver comment mettre à jour le spaceLeft de la zone dans laquelle on a free le block. Pas opti de reparcourir toutes les zones.
// On peut peut etre jouer avec les valeurs des adresses et déduire dans quelle zone se trouve ptr_head : "if (ptr_head) < zone + ZONE_LENGTH"
int		unmap_zone(t_map *zone)
{
	(void)zone;
	return 0;
}

// Cette fonction va vérifier si plusieurs blocks FREE se suivent, et va les rassembler pour en faire un plus gros et sauver de l'espace.
// Pour l'optimisation, on partira du block qui vient d'être FREE,
// du coup il faut voir si on peut merge avec les potentiels blocks FREE précédents.
// A voir également ce qu'on fait des données du t_head qui est dégagé quand on optimise. On le fait pointer sur NULL ? On remet à 0 ?
void	optimize_free_blocks(t_head *ptr_head)
{
	t_head		*next;

	next = ptr_head->next;
	if (ptr_head->next && next->status == FREE)
	{
		ptr_head->size += next->size;
		ptr_head->spaceBeforeNext = next->spaceBeforeNext;
		ptr_head->next = next->next;
		optimize_free_blocks(ptr_head);
	}
}

// Cette fonction va vérifier si on veut free une alloc de type LARGE.
// Si c'est le cas, on unmap la zone.
void	verif_large_free(t_head *ptr_head)
{
	t_map		*tmp;

	tmp = g_zones->large;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->firstHead == ptr_head)
		{
			unmap_zone(tmp);
			break ;
		}
	}
}

// Ici, on va passer le block pointé en FREE si cela concerne une zone TINY ou SMALL.
// Pour une zone LARGE, on va unmap la zone directement.
// On doit egalement se charger d'optimiser les blocks FREE pour avoir les plus grands blocks possible disponibles.
// Doit-on remettre à 0 un block FREE ? Ou sa "mem" doit-elle pointer sur NULL ? A voir.
void	ft_free(void *ptr)
{
	t_head		*ptr_head;
	
	if (!ptr)
		return ;
	ptr_head = ptr - HEAD_SIZE;
	ptr_head->status = FREE;
	ptr_head->mem = NULL; // Impossible, car on n'initialise jamais le mem. A voir si on le fait dans findFreeBlock, ou trouver une autre solution.
	verif_large_free(ptr_head);
	optimize_free_blocks(ptr_head);
}