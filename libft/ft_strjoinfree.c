/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 20:10:11 by oachbani          #+#    #+#             */
/*   Updated: 2025/02/17 14:58:15 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoinfree(char *str1, char *str2)
{
	char	*str;
	size_t	s1len;
	size_t	s2len;

	if (!str1)
	{
		str1 = (char *)malloc(sizeof(char));
		str1[0] = '\0';
	}
	s1len = ft_strlen(str1);
	s2len = ft_strlen(str2);
	str = malloc(sizeof(char) * (s1len + s2len + 1));
	if (!str)
		return (NULL);
	ft_memcpy(str, str1, s1len);
	ft_memcpy(str + s1len, str2, s2len + 1);
	str[s1len + s2len] = '\0';
	free(str1);
	return (str);
}
