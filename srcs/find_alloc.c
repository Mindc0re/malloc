/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:13:12 by sgaudin           #+#    #+#             */
/*   Updated: 2018/11/29 16:13:16 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_head		*find_free_block(size_t size, t_map *zone)
{
	t_head *tmp;

	tmp = zone->first_head;
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
		tmp->sp_before_n += tmp->size - size;
	}
	return (tmp);
}

t_head		*find_free_space(size_t size, t_map *zone)
{
	t_head *tmp;
	t_head *new;

	tmp = zone->first_head;
	while (tmp)
	{
		if (tmp->sp_before_n >= size + HEAD_SIZE)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return (NULL);
	new = tmp->mem + tmp->size;
	new->size = size;
	new->sp_before_n = tmp->sp_before_n - (HEAD_SIZE + size);
	new->status = USED;
	new->mem = tmp->mem + tmp->size + HEAD_SIZE;
	new->next = tmp->next ? tmp->next : NULL;
	tmp->next = new;
	tmp->sp_before_n = 0;
	return (new);
}

t_head		*init_first_head(size_t size, t_map *zone)
{
	zone->first_head = zone->mem;
	zone->first_head->size = size;
	zone->first_head->sp_before_n =
	(zone->type == TINY ? TINY_ZONE : SMALL_ZONE) - HEAD_SIZE - size;
	zone->first_head->status = USED;
	zone->first_head->mem = zone->mem + HEAD_SIZE;
	zone->first_head->next = NULL;
	return (zone->first_head);
}

void		*find_alloc(size_t size, t_map *zone)
{
	t_head	*new;

	if (size > zone->av_space)
		return (NULL);
	if (!zone->first_head)
		new = init_first_head(size, zone);
	else
	{
		new = find_free_block(size, zone);
		if (!new)
			new = find_free_space(size, zone);
	}
	zone->av_space = calc_space_left(zone);
	return (new ? new->mem : NULL);
}
