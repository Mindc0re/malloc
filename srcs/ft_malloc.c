/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:13:38 by sgaudin           #+#    #+#             */
/*   Updated: 2018/11/29 16:13:39 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void			*ft_malloc(size_t size)
{
	void		*alloc;

	pthread_mutex_lock(&g_mutex);
	if (size <= 0)
		return (NULL);
	alloc = NULL;
	if (size > SMALL_ALLOC)
		return (alloc_large_zone(size));
	else if (size > TINY_ALLOC)
	{
		if (!g_zones.small)
			pushback_mem(0, SMALL, &g_zones.small);
		alloc = zone_parser(g_zones.small, size);
	}
	else if (size <= TINY_ALLOC)
	{
		if (!g_zones.tiny)
			pushback_mem(0, TINY, &g_zones.tiny);
		alloc = zone_parser(g_zones.tiny, size);
	}
	pthread_mutex_unlock(&g_mutex);
	return (alloc);
}
