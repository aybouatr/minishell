/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 10:36:22 by oachbani          #+#    #+#             */
/*   Updated: 2024/11/09 10:36:25 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t		i;
	size_t		j;

	if (!str && len == 0)
		return (NULL);
	if (!(*to_find))
		return ((char *)str);
	i = 0;
	while (i < len && str[i])
	{
		j = 0;
		while (str[i + j] == to_find[j] && to_find[j])
			j++;
		if (!to_find[j])
		{
			if (i + ft_strlen(to_find) > len)
				return (NULL);
			return ((char *)str + i);
		}
		i++;
	}
	return (NULL);
}
