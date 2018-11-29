/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zones_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:14:26 by sgaudin           #+#    #+#             */
/*   Updated: 2018/11/29 16:14:27 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		*alloc_large_zone(size_t size)
{
	t_map *tmp;

	if (!pushback_mem(size, LARGE, &g_zones.large))
		return (0);
	tmp = g_zones.large;
	while (tmp->next)
		tmp = tmp->next;
	tmp->first_head = tmp->mem;
	tmp->first_head->size = size;
	tmp->first_head->sp_before_n = 0;
	tmp->first_head->status = USED;
	tmp->first_head->mem = tmp->mem + HEAD_SIZE;
	tmp->first_head->next = NULL;
	return (tmp->first_head->mem);
}

int			alloc_mem(size_t size, int type, t_map **to_alloc)
{
	if (((*to_alloc) = (t_map *)mmap(0, sizeof(t_map), PROT_READ |
		PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == (void *)-1)
		return (0);
	if (((*to_alloc)->mem = mmap(0, size, PROT_READ |
		PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0)) == (void *)-1)
		return (0);
	(*to_alloc)->av_space = type == LARGE ? 0 : size;
	(*to_alloc)->type = type;
	(*to_alloc)->first_head = NULL;
	(*to_alloc)->next = NULL;
	return (1);
}

int			pushback_mem(size_t size, int type, t_map **target_zone)
{
	t_map	*tmp;
	t_map	*new;

	if (type == LARGE)
		size += HEAD_SIZE;
	else
		size = type == TINY ? TINY_ZONE : SMALL_ZONE;
	if (!target_zone || !(*target_zone))
	{
		if (!alloc_mem(size, type, target_zone))
			return (0);
	}
	else
	{
		tmp = (*target_zone);
		while (tmp->next)
			tmp = tmp->next;
		if (!alloc_mem(size, type, &new))
			return (0);
		tmp->next = new;
	}
	return (1);
}
