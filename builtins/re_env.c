/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 16:11:00 by oachbani          #+#    #+#             */
/*   Updated: 2025/04/19 16:45:11 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void	ft_get_envdata()
{
	g_data.cwd= getcwd(NULL, 0);
	g_data.oldpwd = get_oldpwd(g_data.env);
}

void	re_env()
{
	int		i;
	int 	checker;

	ft_get_envdata();
	i = -1;
	checker = -1;
	while(g_data.env[++i])
		if (!ft_strncmp(g_data.env[i], "PATH=", 5))
			checker = 0;
	if (checker == -1)
	{
		printf("minishell: env: No such file or directory\n");
		g_data.exit_status = 127;
		return;
	}
	i = -1;
	while (g_data.env[++i])
		if (ft_strchr(g_data.env[i], '='))
			printf("%s\n", g_data.env[i]);
}
