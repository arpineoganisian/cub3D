/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 18:15:29 by hwoodwri          #+#    #+#             */
/*   Updated: 2020/11/08 15:29:45 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	find_min(size_t a, size_t b)
{
	if (a > b)
		return (b);
	else
		return (a);
}

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t n;

	i = 0;
	if (!src || !dst)
		return (0);
	n = ft_strlen(src);
	if (dstsize != 0)
	{
		if ((i = find_min(n, dstsize - 1)))
			ft_memcpy(dst, src, i);
		dst[i] = '\0';
	}
	return (n);
}
