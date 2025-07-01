/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:14:06 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/11 19:31:51 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != c && str[i])
		i++;
	return (i);
}

static char	*ft_stralloc(char const *str, char c)
{
	int		i;
	char	*p;
	int		x;

	i = ft_len(str, c);
	p = (char *)ft_calloc((i + 1), sizeof(char));
	if (!p)
		return (NULL);
	x = -1;
	while (++x < i)
		p[x] = str[x];
	return (p);
}

static int	count_words(char const *str, char c)
{
	int	word;
	int	count;
	int	i;

	word = 0;
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			word = 0;
		else
		{
			if (word == 0)
				count++;
			word = 1;
		}
		i++;
	}
	return (count);
}

void	ft_free(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
		free(tab[i]);
	free(tab);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	**p;

	if (!s)
		return (NULL);
	p = (char **)ft_calloc((count_words(s, c) + 1), sizeof(char *));
	if (!p)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (!*s)
			break ;
		p[i] = ft_stralloc(s, c);
		if (!p[i++])
		{
			ft_free(p);
			return (NULL);
		}
		while (*s != c && *s)
			s++;
	}
	return (p);
}
