/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 09:40:56 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/11 10:07:01 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_home(char **env)
{
	char	**tmp;

	tmp = env;
	while (*tmp)
	{
		if (ft_strncmp(*tmp, "HOME=", 5) == 0)
			return (*tmp + 5);
		tmp++;
	}
	return (NULL);
}

void	update_pwd(char *cwd)
{
	int		i;
	char	*join;

	join = ft_strjoin("PWD=", cwd);
	i = 0;
	while (g_data.env[i])
	{
		if (ft_strncmp(g_data.env[i], "PWD=", 4) == 0)
		{
			printf("%s  before \n", g_data.env[i]);
			g_data.env[i] = join;
			printf("this is join %s\n", join);
			printf("%s after \n", g_data.env[i]);
		}
		i++;
	}
	free(join);
}

void	update_oldpwd(char *cwd)
{
	int		i;
	char	*join;

	join = ft_strjoin("OLDPWD=", cwd);
	i = 0;
	while (g_data.env[i])
	{
		if (ft_strncmp(g_data.env[i], "OLDPWD=", 7) == 0)
		{
			printf("%s\n", g_data.env[i]);
			g_data.env[i] = join;
		}
		i++;
	}
	ft_get_envdata();
	free(join);
}

int	cd_home(void)
{
	const char	*directory;
	int			i;

	directory = get_home(g_data.env);
	if (!directory)
	{
		printf("minishell : cd: HOME not set\n");
		return (-1);
	}
	i = chdir(directory);
	if (i == -1)
	{
		printf("minishell : failed to change the directory \n");
		return (-1);
	}
	return (0);
}

void	replace_oldpwd(char *oldpwd)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	str = ft_strjoin_gc("OLDPWD=", oldpwd);
	while (g_data.env[i])
	{
		if (ft_strncmp(g_data.env[i], "OLDPWD=", 7) == 0)
		{
			tmp = g_data.env[i];
			g_data.env[i] = ft_strdup_env(str);
			gc_free_one(tmp);
			break ;
		}
		i++;
	}
	free(oldpwd);
}
