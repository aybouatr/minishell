/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:58:54 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/11 09:56:01 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	f(t_2d_list *current)
{
	int	fd;

	fd = open(current->content[1], O_RDONLY, 0644);
	if (fd == -1)
		return (0);
	return (1);
}

void	next_one(t_2d_list **tokens)
{
	while ((*tokens))
	{
		if ((*tokens)->type_token == e_pipe)
		{
			(*tokens) = (*tokens)->next;
			break ;
		}
		(*tokens) = (*tokens)->next;
	}
}

int	dup_to_heredoc(t_2d_list *tokens)
{
	int	fd;

	fd = open(tokens->content[0], O_RDONLY, 0644);
	if (fd == -1)
	{
		dup_intializer();
		g_data.exit_status = EXIT_FAILURE;
		return (-1);
	}
	if (dup2(fd, 0) == -1)
	{
		printf("the dup2 has faild\n");
		return (-1);
	}
	return (1);
}

int	apply_redirection(t_2d_list *tokens)
{
	int	status;

	if (!tokens)
		return (0);
	status = 0;
	while (tokens && tokens->type_token != e_pipe)
	{
		if (tokens->type_token == e_redir_ou)
			status = output_redirection(tokens);
		else if (tokens->type_token == e_redir_app)
			status = append_redirection(tokens);
		else if (tokens->type_token == e_here_doc)
			status = dup_to_heredoc(tokens);
		else if (tokens->type_token == e_redir_in)
			status = input_redirection(tokens);
		if (status == -1)
			return (-1);
		tokens = tokens->next;
	}
	return (0);
}

void	start_execution(t_2d_list *tokens)
{
	int	status;

	status = 0;
	update_global_pipe(tokens);
	while (tokens)
	{
		if (no_pipe(tokens))
		{
			work_with_pipe(&status, &tokens);
			continue ;
		}
		g_data.exit_status = execution_machine(&tokens);
		setup_signals();
		while (wait(NULL) > 0)
			;
		next_one(&tokens);
	}
	dup_intializer();
}
