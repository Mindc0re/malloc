/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:14:19 by sgaudin           #+#    #+#             */
/*   Updated: 2018/11/29 16:14:21 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		p_mem_next(t_head *tmp_head)
{
	ft_put_adress((uintmax_t)tmp_head->mem);
	ft_putstr(" - ");
	ft_put_adress((uintmax_t)tmp_head->mem + tmp_head->size - 1);
	ft_putstr(" : ");
	ft_putnbr(tmp_head->size);
	ft_putstr(" octets\n");
}

int			print_mem(t_map *tmp, char *type)
{
	int		total;
	t_head	*tmp_head;

	total = 0;
	while (tmp)
	{
		tmp_head = tmp->first_head;
		ft_putchar('\n');
		ft_putstr(type);
		ft_putstr(" : ");
		ft_put_adress((uintmax_t)tmp);
		ft_putchar('\n');
		while (tmp_head)
		{
			if (tmp_head->status == USED)
			{
				p_mem_next(tmp_head);
				total += tmp_head->size;
			}
			tmp_head = tmp_head->next;
		}
		tmp = tmp->next;
	}
	return (total);
}

void		show_alloc_mem(void)
{
	t_map	*tmp;
	int		total;

	pthread_mutex_lock(&g_mutex);
	tmp = NULL;
	total = 0;
	tmp = g_zones.tiny;
	if (tmp)
		total += print_mem(tmp, "TINY");
	tmp = g_zones.small;
	if (tmp)
		total += print_mem(tmp, "SMALL");
	tmp = g_zones.large;
	if (tmp)
		total += print_mem(tmp, "LARGE");
	ft_putstr("Total : ");
	ft_putnbr(total);
	ft_putstr(" octets\n");
	pthread_mutex_unlock(&g_mutex);
}
