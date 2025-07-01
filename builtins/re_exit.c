/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 16:01:58 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/10 10:35:10 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_not_digit(char *str)
{
	int	i;

	i = 0;
	if (!(*str))
		return (1);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	check_max(char *str)
{
	int	i;
	int	negative;

	i = 0;
	negative = NO;
	if (str[i] == '-')
		negative = YES;
	if ((str[i] == '+' || str[i] == '-'))
		str++;
	if (ft_strlen(str) > 19)
		return (0);
	if (ft_strlen(str) == 19)
	{
		if (negative == YES && ft_strcmp(str, "9223372036854775808") > 0)
			return (0);
		else if (negative == NO && ft_strcmp(str, "9223372036854775807") > 0)
			return (0);
	}
	return (1);
}

void	re_exit(char **str)
{
	if (g_data.pipe == NO)
		printf("exit\n");
	if (str[1])
	{
		if (!check_max(str[1]) || ft_not_digit(str[1]))
		{
			printf("minishell : exit: %s: numeric argument required\n", str[1]);
			clean_all("", 2);
			exit(2);
		}
		else if (str[2])
		{
			printf("minishell: exit: too many arguments\n");
			g_data.exit_status = 1;
			return ;
		}
		else
		{
			g_data.exit_status = ft_atoi(str[1]);
			clean_all("", g_data.exit_status);
			exit(g_data.exit_status);
		}
	}
	return (clean_memory("", 1), clean_env(), exit(EXIT_SUCCESS));
}
