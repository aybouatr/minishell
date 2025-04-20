/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:34:45 by oachbani          #+#    #+#             */
/*   Updated: 2025/04/19 17:28:22 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_home(char **env)
{
	char **tmp;

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
	int	i;
	char *join;
	char *joinnl;

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
	int	i;
	char *join;

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
	// update_pwd(g_data.cwd);
	free(join);
}

int	cd_home(void)
{
	const char *directory;
	int 		i;

	directory = get_home(g_data.env);
	if (!directory)
	{
		printf("minishell : cd: HOME not set\n");
		return(-1);
	}
	i = chdir (directory);
	if (i == -1)
	{
		printf("minishell : failed to change the directory \n");
		return (-1);
	}
}

int	cd_path(char *str)
{
	int i;

	i = chdir(str);
	if (i == -1)
	{
		printf("minishell : cd: %s: No such file or directory\n", str);
		return (-1);
	}
}

char	*get_oldpwd(char **env)
{
	char **tmp;

	tmp = env;
	while (*tmp)
	{
		if (ft_strncmp(*tmp, "OLDPWD=", 7) == 0)
			return (*tmp + 7);
		tmp++;
	}
	return (NULL);
}

void	re_cd(char *str)
{
	int		status;
	int		pos;

	pos = 0;
	status = 0;

	ft_get_envdata();
	if (!str || !ft_strcmp(str, "--"))
		status = cd_home();
	else if (!ft_strcmp(str, "."))
		status = cd_path(g_data.cwd);
	else if (!ft_strcmp(str, "-"))
	{
		if (!g_data.oldpwd)
			printf("minishell: cd: OLDPWD not set");
		status = cd_path(g_data.oldpwd);
		if (status != -1)
			printf("%s\n", g_data.cwd);
	}
	else if (str)
		status = cd_path(str);
	if (status == -1)
		g_data.exit_status = 1;
}

