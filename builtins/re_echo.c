/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:11:55 by oachbani          #+#    #+#             */
/*   Updated: 2025/04/12 11:16:10 by oachbani         ###   ########.fr       */
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
	if (!ft_strcmp(str[1], "-n"))
		i++;
	while (str[++i])
	{
		printf("%s", str[i]);
		if (str[i + 1])
			printf(" ");
	}
	if (ft_strcmp(str[1], "-n"))
		printf("\n");
}
