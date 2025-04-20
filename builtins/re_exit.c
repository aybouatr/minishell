/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:01:58 by oachbani          #+#    #+#             */
/*   Updated: 2025/04/15 15:26:48 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_not_digit(char *str)
{
	int	i;

	i = 0;
	if (!(*str))
		return(1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return(1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return(1);
	i++;
	}
	return(0);
}

void	re_exit(char **str)
{
	printf("exit\n");
	if (str[1])
	{
		if (ft_not_digit(str[1]))
		{
			printf("minishell : exit: %s: numeric argument required\n", str[1]);
			exit(2);
		}
		else if (str[2])
		{
			printf("minishell: exit: too many arguments");
			g_data.exit_status = 1;
			return ;
		}
		else
		{
			g_data.exit_status = ft_atoi(str[1]);
			exit(g_data.exit_status);
		}
	}
	exit(EXIT_SUCCESS);
}