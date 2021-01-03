/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 19:42:59 by hwoodwri          #+#    #+#             */
/*   Updated: 2020/11/08 15:31:33 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		num_of_dig(int n)
{
	int tmp;
	int x;

	tmp = 1;
	x = n;
	while ((x = x / 10))
		tmp = tmp * 10;
	return (tmp);
}

void			ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		tmp;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
	}
	if (n >= 0)
	{
		tmp = num_of_dig(n);
		while (tmp)
		{
			c = n / tmp + '0';
			write(fd, &c, 1);
			n = n % tmp;
			tmp = tmp / 10;
		}
	}
}
