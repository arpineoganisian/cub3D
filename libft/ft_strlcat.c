/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 13:34:24 by hwoodwri          #+#    #+#             */
/*   Updated: 2020/11/05 14:57:52 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t len;
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	len = ft_strlen(dst) + ft_strlen(src);
	if (ft_strlen(dst) > dstsize)
		return (ft_strlen(src) + dstsize);
	else
	{
		while (dst[i])
		{
			dstsize--;
			i++;
		}
		while (src[j] && dstsize > 1)
		{
			dst[i++] = src[j++];
			dstsize--;
		}
		dst[i] = '\0';
	}
	return (len);
}
