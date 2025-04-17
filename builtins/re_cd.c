/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:34:45 by oachbani          #+#    #+#             */
/*   Updated: 2025/04/12 11:16:08 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cd_home(void)
{
	const char *directory;
	int 		i;

	directory = getenv("HOME");
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

void	re_cd(char *str)
{
	int		status;

	status = 0;
	ft_get_envdata();
	if (!str)
		status = cd_home();
	else if (str)
		status = cd_path(str);
	else if (!ft_strcmp(str, "."))
		status = cd_path(g_data.cwd);
	else if (!ft_strcmp(str, "-"))
	{
		ft_get_envdata();
		if (!g_data.oldpwd)
			printf("minishell: cd: OLDPWD not set");
		status = cd_path(g_data.oldpwd);
		if (status != -1)
			printf("%s\n", g_data.cwd);
	}
	if (status == -1)
		g_data.exit_status = 1;
}

