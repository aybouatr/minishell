/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 15:55:26 by oachbani          #+#    #+#             */
/*   Updated: 2025/04/13 11:37:18 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quote_value(int i)
{
	char	*value;
	int		j;

	j = -1;
	value = ft_strchr (g_data.env[i] , '=');
	if (value)
	{
		printf("declare -x ");
		while(g_data.env[i][++j] != '=')
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
	return(i);
}

char *del_fplus(char *str)
{
	char	*new;
	int		i;

	i = 0;
	new = ft_strdup(str);
	while(new[i] && new[i] != '+')
		i++;
	if (new[i] == '+')
	{
		while(new[i])
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
				return(-2);
			if (g_data.env[i][len] == '='|| !g_data.env[i][len])
				return(i);
		}
		i++;
	}
	return(-1);
}

void	print_export(void)
{
	int	i;

	i = -1;
	while (g_data.env[++i])
	{
		if (!ft_strchr(g_data.env[i], '='))
			printf("declare -x %s \n",g_data.env[i]);
		else
			quote_value(i);
	}
}

char **add_new(char *str)
{
	int	len;
	char	**new;

	len = tab_counter(g_data.env);
	new = malloc((len + 2) * sizeof(char *));
	len = 0;
	while (g_data.env[len])
	{
		new[len] = ft_strdup(g_data.env[len]);
		if (!new[len])
		{
			ft_free(new);
			return (NULL);
		}
		len++;
	}
	new[len++] = ft_strdup(str);
	new[len] = NULL;
	ft_free(g_data.env);
	return(new);
}

void	edit_var(int i, char *str)
{
	free(g_data.env[i]);
	g_data.env[i] = ft_strdup(str);
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
	str++;
	if (*str == '=')
		str++;
	g_data.env[index] = ft_strjoinfree(g_data.env[index] ,str);
}

int	check_the_special(char *s)
{
	int	i;
	int	equ_len;

	i = -1;
	equ_len = ft_equal_len(s);
	while(++i < equ_len)
		if (!ft_isalnum(s[i]) && s[i] != '+' && s[i] != '=')
			return (0);
	return(1);
}
int	export_it(char *str)
{
	int		i;
	char	*export;
	char	*new;

	i = 0;
	if (!ft_isalpha(str[i]))
	{
		printf("minishell: export: `%s': not a valid identifier\n", str);
		return(1);
	}
	if (!check_the_special(str))
	{
		printf("minishell: export: `%s': not a valid identifier\n", str);
		return(1);
	}	
	export = ft_strchr(str, '+');
	if (export)
	{
		if (export[i + 1] != '=')
			return (printf("minishell: export: `%s': not a valid identifier\n", str), 0);
		new = del_fplus(str);
		join_the_value(export, new);
		free(new);
	}
	else
		export_value(str);
	return(0);
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

	i = 0;
	if (!str[1])
		print_export();
	else if (str[1])
	{
		while(str[++i])
			g_data.exit_status = export_it(str[i]);
		sort_env();
	}
}
