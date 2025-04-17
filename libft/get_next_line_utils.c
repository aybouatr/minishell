/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:39:17 by oachbani          #+#    #+#             */
/*   Updated: 2025/02/11 19:53:47 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchrget(char *str, int c)
{
	int	i;

	if (!str)
		return (NULL);
	i = -1;
	while (str[++i])
		if (str[i] == (char)c)
			return ((char *)&str[i]);
	if (str[i] == (char)c)
		return ((char *)&str[i]);
	return (NULL);
}

size_t	ft_strlenget(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdupget(char *s)
{
	size_t	i;
	char	*p;

	i = ft_strlenget(s);
	p = (char *)malloc(i + 1);
	if (!p)
		return (NULL);
	i = -1;
	while (s[++i])
		p[i] = s[i];
	p[i] = '\0';
	return (p);
}

char	*ft_strjoinget(char *s1, char *s2)
{
	size_t	i;
	char	*p;
	int		j;

	if (!s1)
		s1 = ft_strdupget("");
	if (!s1 || !s2)
		return (NULL);
	i = ft_strlenget(s1) + ft_strlenget(s2);
	p = malloc(i + 1);
	if (!p)
		return (free(s1), NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		p[i] = s1[i];
	while (s2[++j])
		p[i++] = s2[j];
	p[i] = '\0';
	free(s1);
	return (p);
}
