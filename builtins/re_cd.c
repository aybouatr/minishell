/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:34:45 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/11 10:06:15 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	replace_pwd(void)
{
	int		i;
	char	*str;
	char	*tmp;

	i = 0;
	str = ft_strjoin_gc("PWD=", g_data.cwd);
	while (g_data.env[i])
	{
		if (ft_strncmp(g_data.env[i], "PWD=", 4) == 0)
		{
			tmp = g_data.env[i];
			g_data.env[i] = ft_strdup_env(str);
			gc_free_one(tmp);
			break ;
		}
		i++;
	}
}

int	cd_path(char *str)
{
	int		i;
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	i = chdir(str);
	if (i == -1)
	{
		printf("minishell : cd: %s: No such file or directory\n", str);
		return (-1);
	}
	replace_oldpwd(oldpwd);
	ft_get_envdata();
	replace_pwd();
	return (0);
}

char	*get_oldpwd(char **env)
{
	char	**tmp;
	char	*oldpwd;
	size_t	len;

	tmp = env;
	while (*tmp)
	{
		if (ft_strncmp(*tmp, "OLDPWD=", 7) == 0)
		{
			len = ft_strlen(*tmp + 7);
			oldpwd = allocation(len + 1);
			if (oldpwd)
				ft_strlcpy(oldpwd, *tmp + 7, len + 1);
			return (oldpwd);
		}
		tmp++;
	}
	return (NULL);
}

void	error_custom(char *str, int exit)
{
	printf("%s\n", str);
	g_data.exit_status = exit;
}

void	re_cd(char *str)
{
	int	status;
	int	pos;

	pos = 0;
	status = 0;
	ft_get_envdata();
	if (!str)
		status = cd_home();
	else if (!ft_strcmp(str, "."))
		status = cd_path(g_data.cwd);
	else if (!ft_strcmp(str, "-"))
	{
		if (!g_data.oldpwd)
		{
			error_custom("minishell: cd: OLDPWD not set", 1);
			return ;
		}
		status = cd_path(g_data.oldpwd);
		if (status != -1)
			printf("%s\n", g_data.cwd);
	}
	else if (str)
		status = cd_path(str);
	if (status == -1)
		g_data.exit_status = 1;
}
