/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:44:18 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/11 10:07:39 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quote_value(int i)
{
	char	*value;
	int		j;

	j = -1;
	value = ft_strchr(g_data.env[i], '=');
	if (value)
	{
		printf("declare -x ");
		while (g_data.env[i][++j] != '=')
			printf("%c", g_data.env[i][j]);
		value++;
		printf("=\"%s\"\n", value);
	}
}

int	ft_equal_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (i);
}

char	*del_fplus(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_strdup(str);
	while (new[i] && new[i] != '+')
		i++;
	if (new[i] == '+')
	{
		while (new[i])
		{
			new[i] = new[i + 1];
			i++;
		}
	}
	return (new);
}

int	search_for_export(char *search)
{
	int	i;
	int	len;

	i = 0;
	len = ft_equal_len(search);
	while (g_data.env[i])
	{
		if (!ft_strncmp(g_data.env[i], search, len))
		{
			if (g_data.env[i][len] == '=' && !search[len])
				return (-2);
			if (g_data.env[i][len] == '=' || !g_data.env[i][len])
				return (i);
		}
		i++;
	}
	return (-1);
}

void	print_export(void)
{
	int	i;

	i = -1;
	sort_env();
	while (g_data.env[++i])
	{
		if (!ft_strchr(g_data.env[i], '='))
			printf("declare -x %s \n", g_data.env[i]);
		else
			quote_value(i);
	}
}
