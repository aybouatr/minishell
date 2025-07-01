/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:47:16 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/11 10:06:30 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**del_tab_2d_arr(int del)
{
	while (g_data.env[del + 1])
	{
		g_data.env[del] = g_data.env[del + 1];
		del++;
	}
	g_data.env[del] = NULL;
	return (g_data.env);
}

int	search_the_env(char *search)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(search);
	while (g_data.env[i])
	{
		if (!ft_strncmp(g_data.env[i], search, len))
			if (g_data.env[i][len] == '=' || !g_data.env[i][len])
				return (i);
		i++;
	}
	return (-1);
}

void	re_unset(char **str)
{
	int	removable;
	int	i;

	if (!str || !*str)
		return ;
	i = 1;
	while (str[i])
	{
		removable = search_the_env(str[i]);
		if (removable != -1)
			g_data.env = del_tab_2d_arr(removable);
		i++;
	}
}
