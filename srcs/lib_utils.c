/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:13:59 by sgaudin           #+#    #+#             */
/*   Updated: 2018/11/29 16:13:59 by sgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	char			*temp_src;
	char			*temp_dst;
	unsigned int	i;

	temp_src = (char*)src;
	temp_dst = dst;
	i = 0;
	if (n > 0)
	{
		while (i < n)
		{
			temp_dst[i] = temp_src[i];
			i++;
		}
	}
	return (dst);
}

void	ft_putstr(char const *s)
{
	write(1, s, ft_strlen(s));
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(uintmax_t n)
{
	if (n >= 10)
		ft_putnbr(n / 10);
	ft_putchar((n % 10) + '0');
}

void	ft_put_adress(uintmax_t n)
{
	static int	add = 0;

	if (!add)
	{
		write(1, "0x", 2);
		add = 1;
	}
	if (n >= 16)
	{
		ft_put_adress(n / 16);
		add = 1;
		n %= 16;
	}
	add = 0;
	ft_putchar((n % 16) >= 10 ? (n % 10) + 'a' : (n % 16) + '0');
}
