/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 14:55:14 by oachbani          #+#    #+#             */
/*   Updated: 2024/11/09 12:07:55 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char			*destination;
	char			*source;
	size_t			i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	destination = dest;
	source = (void *)src;
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (destination);
}
