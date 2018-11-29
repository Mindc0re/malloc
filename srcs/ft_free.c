/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:13:30 by sgaudin           #+#    #+#             */
/*   Updated: 2018/11/29 16:13:31 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int			is_unused(t_map *zone)
{
	t_head *tmp;

	if (!zone)
		return (0);
	if (zone->type == LARGE)
		return (1);
	tmp = zone->first_head;
	while (tmp)
	{
		if (tmp->status == USED)
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void		unmap_zone_next(t_map **zone, size_t m_size, t_map **tmp, int *chk)
{
	if ((*tmp) == g_zones.large && (*tmp)->next == NULL)
		(*chk) = 1;
	(*tmp)->next = (*zone)->next;
	munmap((*zone)->mem, m_size);
	munmap((*zone), sizeof((*zone)));
	if ((*chk) == 1)
		g_zones.large = NULL;
}

int			unmap_zone(t_map *zone, size_t map_size)
{
	t_map	*tmp;
	t_map	*tmp_next;
	int		check;

	check = 0;
	tmp_next = NULL;
	if (!zone || !is_unused(zone))
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
	unmap_zone_next(&zone, map_size, &tmp, &check);
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
		ptr_head->sp_before_n = next->sp_before_n;
		ptr_head->next = next->next;
		optimize_free_blocks(ptr_head);
	}
}

void		free(void *ptr)
{
	t_head	*ptr_head;
	t_map	*z_ptr;

	pthread_mutex_lock(&g_mutex);
	if (!ptr)
		return ;
	ptr_head = ptr - HEAD_SIZE;
	z_ptr = which_zone(ptr_head);
	if (!z_ptr)
		return ;
	if (z_ptr->type == LARGE)
	{
		unmap_zone(z_ptr, z_ptr->first_head->size);
		return ;
	}
	ptr_head->status = FREE;
	z_ptr->av_space += ptr_head->size;
	if (!unmap_zone(z_ptr, z_ptr->type == SMALL ? SMALL_ZONE : TINY_ZONE))
		optimize_free_blocks(ptr_head);
	pthread_mutex_unlock(&g_mutex);
}
