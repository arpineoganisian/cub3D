/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:03:51 by hwoodwri          #+#    #+#             */
/*   Updated: 2020/11/08 13:58:10 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*s2;
	int				i;
	unsigned int	min;

	i = 0;
	if (!s || len <= 0 || start >= ft_strlen(s))
		return (ft_strdup(""));
	min = ft_strlen(&s[start]);
	if (min < len)
		len = min;
	s2 = (char*)malloc(sizeof(char) * (len + 1));
	if (!s2)
		return (0);
	while (s[i] && 0 < len)
	{
		s2[i] = s[start];
		i++;
		start++;
		len--;
	}
	s2[i] = '\0';
	return (s2);
}
