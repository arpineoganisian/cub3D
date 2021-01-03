/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 15:56:06 by hwoodwri          #+#    #+#             */
/*   Updated: 2020/11/12 15:19:36 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	neelen;

	i = 0;
	if (!*needle || haystack == needle)
		return ((char *)haystack);
	if (ft_strlen(needle) > ft_strlen(haystack) || len == 0)
		return (0);
	neelen = ft_strlen((char *)needle);
	while (i < (len - neelen + 1) && haystack[i])
	{
		if (haystack[i] == needle[0])
		{
			if (ft_strncmp(haystack + i, needle, neelen) == 0)
				return ((char *)haystack + i);
		}
		i++;
	}
	return (0);
}
