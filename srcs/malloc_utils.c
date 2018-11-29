/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:14:13 by sgaudin           #+#    #+#             */
/*   Updated: 2018/11/29 16:14:13 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

int		calc_space_left(t_map *zone)
{
	t_head	*tmp;
	int		head_count;
	int		total_size;
	int		zone_size;

	head_count = 0;
	total_size = 0;
	zone_size = zone->type == TINY ? TINY_ZONE : SMALL_ZONE;
	tmp = zone->first_head;
	while (tmp)
	{
		head_count++;
		total_size += tmp->size;
		tmp = tmp->next;
	}
	return (zone_size - (head_count * HEAD_SIZE) - total_size);
}

void	*zone_parser(t_map *zone, size_t size)
{
	void		*ret_new_alloc;
	t_map		*tmp;

	tmp = zone;
	while (tmp)
	{
		if (tmp->av_space > size + HEAD_SIZE)
		{
			ret_new_alloc = find_alloc(size, tmp);
			if (ret_new_alloc)
				return (ret_new_alloc);
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (!pushback_mem(0, tmp->type, &tmp))
		return (NULL);
	else
		return (zone_parser(tmp, size));
}
