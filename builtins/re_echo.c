/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:11:55 by oachbani          #+#    #+#             */
/*   Updated: 2025/04/16 13:47:37 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void re_echo(char **str)
{
	int i ;

	i = 0;
	if (!str[i + 1])
	{
		printf("\n");
		return	;
	}
	// if (!ft_strncmp(str[1], "$?",2))
	// {
	// 	printf("%s\n", g_data.exit_status);
	// 	return;
	// }
	i = 1;
	while (str[i] && !ft_strcmp(str[i], "-n"))
		i++;
	while (str[i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strcmp(str[1], "-n"))
		printf("\n");
}
