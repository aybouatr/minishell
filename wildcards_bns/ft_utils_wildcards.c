/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_wildcards.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:25:17 by aybouatr          #+#    #+#             */
/*   Updated: 2025/04/08 11:25:20 by aybouatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*grbc_strdup(const char *s)
{
	size_t	i;
	char	*p;

	i = ft_strlen(s);
	p = (char *)allocation((i + 1) * sizeof(char));
	if (!p)
		return (NULL);
	i = -1;
	while (s[++i])
		p[i] = s[i];
	p[i] = '\0';
	return (p);
}

int	ft_fnmatch(const char *pattern, char *name_file)
{
	char	**arr;
	int		index;
	char	*patter_n;

	index = 0;
	patter_n = name_file;
	if (pattern == NULL || name_file == NULL)
		return (1);
	if (ft_strlen(pattern) == 1 && 0 == strcmp(pattern, "*"))
		return (0);
	arr = ft_split(pattern, '*');
	while (arr && arr[index])
	{
		patter_n = ft_strnstr(patter_n, arr[index], ft_strlen(name_file));
		if (patter_n == NULL)
			return (ft_free(arr), 1);
		index++;
	}
	ft_free(arr);
	return (0);
}
