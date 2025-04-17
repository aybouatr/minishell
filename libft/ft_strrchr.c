/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 19:35:01 by oachbani          #+#    #+#             */
/*   Updated: 2024/11/09 09:27:34 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*lst;
	int		i;

	i = -1;
	lst = NULL;
	while (str[++i])
		if (str[i] == (char) c)
			lst = (char *) &str[i];
	if (str[i] == (char) c)
		lst = (char *) &str[i];
	return (lst);
}
