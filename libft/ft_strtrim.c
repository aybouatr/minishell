/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:00:08 by oachbani          #+#    #+#             */
/*   Updated: 2024/11/06 10:26:06 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char const *sep, char c)
{
	int	i;

	i = -1;
	while (sep[++i])
		if (sep[i] == c)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	e;
	size_t	s;

	if (!s1 || !set)
		return (NULL);
	s = 0;
	while (s1[s] && is_set(set, s1[s]))
		s++;
	e = ft_strlen(s1);
	while (s < e && is_set(set, s1[e - 1]))
		e--;
	return (ft_substr(s1, s, e - s));
}
