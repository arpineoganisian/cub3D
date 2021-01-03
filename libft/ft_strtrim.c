/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwoodwri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 18:24:32 by hwoodwri          #+#    #+#             */
/*   Updated: 2020/11/12 15:23:40 by hwoodwri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		setcheck(char s, char const *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == s)
			return (1);
		i++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char			*s2;
	int				i;
	unsigned int	start;
	size_t			len;

	i = 0;
	start = 0;
	len = 0;
	if (!s1 || !set)
		return (NULL);
	while (setcheck(s1[i], set) == 1)
		i++;
	if ((ft_strlen(s1) - i) == 0)
		return (ft_strdup(""));
	start = i;
	i = ft_strlen(s1) - 1;
	while (setcheck(s1[i], set) == 1)
		i--;
	len = i - start + 1;
	s2 = ft_substr(s1, start, len);
	return (s2);
}
