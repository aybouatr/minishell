/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:36:39 by oachbani          #+#    #+#             */
/*   Updated: 2024/11/07 13:55:33 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*p;
	size_t		slen;
	size_t		i;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start > (unsigned int)slen)
		return (ft_strdup(""));
	if (len + start >= slen)
		p = (char *)ft_calloc(slen - start + 1, sizeof(char));
	else
		p = (char *)ft_calloc(len + 1, sizeof(char));
	if (!p)
		return (NULL);
	i = 0;
	while (s[start] && i < len)
	{
		p[i] = s[start];
		start++;
		i++;
	}
	return (p);
}
