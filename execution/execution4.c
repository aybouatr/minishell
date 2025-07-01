/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:31:32 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/11 09:54:00 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	open_skip(t_2d_list *files)
{
	while (files && files->type_token != e_pipe)
	{
		if (files->type_token == e_redir_ou)
		{
			if (!output_redirection(files))
			{
				return (-1);
			}
		}
		else if (files->type_token == e_redir_app)
		{
			if (!append_redirection(files))
			{
				return (-1);
			}
		}
		files = files->next;
	}
	return (0);
}

int	for_builtin(t_2d_list *tokens)
{
	int	status;

	if (!tokens)
		return (-1);
	status = apply_redirection(tokens);
	if (status == -1)
		return (-1);
	apply_builtin(tokens);
	return (g_data.exit_status);
}

int	no_pipe(t_2d_list *tokens)
{
	t_2d_list	*copy;

	copy = tokens;
	while (copy && copy->next && copy->next->type_token != e_pipe)
	{
		copy = copy->next;
	}
	if (copy->next && copy->next->type_token == e_pipe)
	{
		return (1);
	}
	return (0);
}

int	update_global_pipe(t_2d_list *tokens)
{
	t_2d_list	*copy;

	if (!tokens)
		return (0);
	copy = tokens;
	while (copy && copy->next && copy->next->type_token != e_pipe)
	{
		copy = copy->next;
	}
	if (copy->next && copy->next->type_token == e_pipe)
	{
		g_data.pipe = YES;
		return (1);
	}
	g_data.pipe = NO;
	return (0);
}

void	skip_no_cmd(t_2d_list **tokens)
{
	while ((*tokens) && (*tokens)->type_token != e_pipe
		&& (*tokens)->type_token != e_cmd
		&& (*tokens)->type_token != e_builtins)
	{
		(*tokens) = (*tokens)->next;
	}
	if ((*tokens) && (*tokens)->type_token == e_pipe)
	{
		exit(0);
	}
}
