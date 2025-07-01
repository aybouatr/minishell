/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:55:26 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/11 10:07:26 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_it(char *str)
{
	int		i;
	char	*export;
	char	*new;

	i = 0;
	if (!ft_isalpha(str[i]))
		return (printf("minishell: export: `%s': not a valid identifier\n",
				str), 1);
	if (!check_the_special(str))
		return (printf("minishell: export: `%s': not a valid identifier\n",
				str), 1);
	export = ft_strchr(str, '+');
	if (export)
	{
		if (export[i + 1] != '=')
			return (printf("minishell: export: `%s': not a valid identifier\n",
					str), 1);
		new = del_fplus(str);
		join_the_value(export, new);
		free(new);
	}
	else
		export_value(str);
	return (0);
}

void	sort_env(void)
{
	char	*tmp;
	int		i;
	int		j;

	i = -1;
	while (g_data.env[++i])
	{
		j = i;
		while (g_data.env[++j])
		{
			if (ft_strcmp(g_data.env[i], g_data.env[j]) > 0)
			{
				tmp = g_data.env[i];
				g_data.env[i] = g_data.env[j];
				g_data.env[j] = tmp;
			}
		}
	}
}

void	re_export(char **str)
{
	int	i;

	g_data.exit_status = 0;
	i = 0;
	if (!str[1])
		print_export();
	else if (str[1])
	{
		while (str[++i])
		{
			if (export_it(str[i]) == 1)
				g_data.exit_status = 1;
		}
		sort_env();
	}
}
