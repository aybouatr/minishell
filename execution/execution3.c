/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:29:20 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/09 19:51:20 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	continue_builtins(t_2d_list *tokens)
{
	if (ft_strcmp(tokens->content[0], "pwd") == 0)
	{
		re_pwd();
		return (clean_all("", g_data.exit_status), exit(g_data.exit_status));
	}
	if (ft_strcmp((char *)tokens->content[0], "unset") == 0)
	{
		re_unset((char **)tokens->content);
		return (clean_all("", g_data.exit_status), exit(g_data.exit_status));
	}
	if (ft_strcmp(tokens->content[0], "cd") == 0)
	{
		if (tokens->content[2])
		{
			printf("minishell : cd: too many arguments\n");
			return (clean_all("", 1), exit(1));
		}
		re_cd(tokens->content[1]);
		return (clean_all("", g_data.exit_status), exit(g_data.exit_status));
	}
}

void	apply_builtin_forked(t_2d_list *tokens)
{
	if (!tokens || !tokens->content || !tokens->content[0])
		return ;
	if (ft_strcmp(tokens->content[0], "export") == 0)
	{
		re_export((char **)tokens->content);
		return (clean_all("", g_data.exit_status), exit(g_data.exit_status));
	}
	if (ft_strcmp(tokens->content[0], "env") == 0)
	{
		re_env();
		return (clean_all("", g_data.exit_status), exit(g_data.exit_status));
	}
	if (ft_strcmp(tokens->content[0], "echo") == 0)
	{
		re_echo((char **)tokens->content);
		return (clean_all("", g_data.exit_status), exit(g_data.exit_status));
	}
	if (ft_strcmp(tokens->content[0], "exit") == 0)
	{
		re_exit((char **)tokens->content);
		return (clean_all("", g_data.exit_status), exit(g_data.exit_status));
	}
	continue_builtins(tokens);
}

int	apply_builtin(t_2d_list *tokens)
{
	if (ft_strcmp(tokens->content[0], "pwd") == 0)
		re_pwd();
	if (ft_strcmp(tokens->content[0], "cd") == 0)
	{
		if (tokens->content[2])
			return (printf("minishell : cd: too many arguments\n"), 1);
		re_cd(tokens->content[1]);
		return (1);
	}
	if (ft_strcmp(tokens->content[0], "echo") == 0)
		re_echo((char **)tokens->content);
	if (ft_strcmp((char *)tokens->content[0], "env") == 0)
		re_env();
	if (ft_strcmp((char *)tokens->content[0], "unset") == 0)
		re_unset((char **)tokens->content);
	if (ft_strcmp((char *)tokens->content[0], "exit") == 0)
		re_exit((char **)tokens->content);
	if (ft_strcmp((char *)tokens->content[0], "export") == 0)
		re_export((char **)tokens->content);
	return (0);
}

int	input_redi(t_2d_list **tokens)
{
	if ((*tokens)->type_token == e_redir_in)
	{
		if (!input_redirection((*tokens)))
		{
			clean_memory("", 0);
			g_data.exit_status = 1;
			return (10);
		}
		if ((*tokens)->next)
			(*tokens) = (*tokens)->next;
	}
	g_data.exit_status = 0;
	return (0);
}

t_2d_list	*for_multiple_rediou(t_2d_list *tokens)
{
	t_2d_list	*redirect_list;
	t_2d_list	*current;

	redirect_list = NULL;
	current = tokens;
	while (current && current->type_token != e_pipe)
	{
		if (current && (current->type_token == e_redir_ou
				|| current->type_token == e_redir_app))
		{
			if (!redirect_list)
				redirect_list = current;
		}
		if (current->next)
			current = current->next;
		else
			break ;
	}
	return (redirect_list);
}
