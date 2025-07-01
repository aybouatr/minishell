/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:35:29 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/09 19:55:13 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_next_check(t_2d_list *tokens)
{
	if (!tokens)
		return (0);
	if (!tokens->next && (tokens->type_token == e_redir_in
			|| tokens->type_token == e_here_doc))
		return (0);
	return (1);
}

int	cold_arms(char *line, char *limiter)
{
	char	*join;

	join = ft_strjoin(limiter, "\n");
	if (ft_strncmp(join, line, ft_strlen(limiter) + 1) == 0)
	{
		free(join);
		return (2);
	}
	free(join);
	return (0);
}

char	*add_nl(char *str)
{
	char	*join;

	join = ft_strjoin_gc(str, "\n");
	return (join);
}

char	*del_nl(char *str)
{
	int	len;

	len = ft_strlen(str) - 1;
	if (str[len] == '\n')
		str[len] = '\0';
	return (str);
}

void	for_norm(int check, char **line, char **new)
{
	if (check != 1)
	{
		*line = del_nl(*line);
		*new = get_arg_expand_for_here_doc(*line);
		*new = add_nl(*new);
	}
	else
	{
		*new = *line;
	}
}
