/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 15:20:48 by oachbani          #+#    #+#             */
/*   Updated: 2024/11/06 12:33:53 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	len(int nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
		len++;
	while (nb)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*p;
	int		i;
	long	nbr;

	nbr = n;
	i = len(n);
	p = (char *)ft_calloc(i + 1, sizeof(char));
	if (!p)
		return (NULL);
	if (nbr < 0)
	{
		p[0] = '-';
		nbr = -nbr;
	}
	else if (nbr == 0)
	{
		p[0] = '0';
		return (p);
	}
	while (nbr > 0)
	{
		p[--i] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (p);
}
