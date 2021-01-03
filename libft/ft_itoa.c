/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:52:25 by hwoodwri          #+#    #+#             */
/*   Updated: 2020/12/07 22:27:08 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(long n)
{
	int x;
	int len;

	len = 0;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	x = n;
	if (n > 0)
	{
		while (x != 0)
		{
			x = x / 10;
			len++;
		}
	}
	return (len);
}

char		*ft_itoa(int n)
{
	int		len;
	char	*str;

	len = length(n);
	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	str = (char*)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	if (n < 0)
	{
		n = -n;
		str[0] = '-';
	}
	while (n)
	{
		str[len] = n % 10 + 48;
		n = n / 10;
		len--;
	}
	return (str);
}
