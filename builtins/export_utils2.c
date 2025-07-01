/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:47:09 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/11 10:07:58 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**add_new(char *str)
{
	int		len;
	char	**new;

	len = tab_counter(g_data.env);
	new = allocation_env((len + 2) * sizeof(char *));
	len = 0;
	while (g_data.env[len])
	{
		new[len] = ft_strdup_env(g_data.env[len]);
		len++;
	}
	new[len++] = ft_strdup_env(str);
	new[len] = NULL;
	return (new);
}

void	edit_var(int i, char *str)
{
	g_data.env[i] = ft_strdup_env(str);
}

void	export_value(char *str)
{
	int	len;
	int	index;

	len = tab_counter(g_data.env);
	index = search_for_export(str);
	if (index == -1)
		g_data.env = add_new(str);
	else if (index == -2)
		return ;
	else
		edit_var(index, str);
}

void	join_the_value(char *str, char *new)
{
	int	index;

	index = search_for_export(new);
	if (index == -1)
	{
		g_data.env = add_new(new);
		return ;
	}
	if (index == -2)
		return ;
	str++;
	if (*str == '=')
		str++;
	if (!ft_strchr(g_data.env[index], '='))
		g_data.env[index] = ft_strjoin_gc(g_data.env[index], "=");
	g_data.env[index] = ft_strjoin_gc(g_data.env[index], str);
}

int	check_the_special(char *s)
{
	int	i;
	int	equ_len;

	i = -1;
	equ_len = ft_equal_len(s);
	while (++i < equ_len)
		if (!ft_isalnum(s[i]) && s[i] != '+' && s[i] != '=')
			return (0);
	return (1);
}
