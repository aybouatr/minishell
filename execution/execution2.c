/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:27:41 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/11 19:32:09 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_pipe(t_2d_list **tokens)
{
	while ((*tokens) && (*tokens)->type_token != e_pipe)
		(*tokens) = (*tokens)->next;
	if ((*tokens) && (*tokens)->type_token == e_pipe)
		(*tokens) = (*tokens)->next;
}

int	work_with_pipe(int *status, t_2d_list **tokens)
{
	int		pipefd[2];
	pid_t	pid;

	pipe(pipefd);
	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		if (apply_redirection(*tokens) == -1)
			return (clean_all("", 1), exit(1), 1);
		skip_no_cmd(tokens);
		execute_command(*tokens);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
	}
	close(pipefd[0]);
	skip_pipe(tokens);
	return (exit_status(*status));
}

void	error(int i)
{
	(void)i;
	ft_putstr_fd("Error ", 2);
	g_data.exit_status = 1;
}

void	waitforchild(pid_t pid, int *status)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	if (waitpid(pid, status, 0) == -1)
	{
		printf("minishell : waitpidfailed\n");
		g_data.exit_status = EXIT_FAILURE;
	}
	if (WIFSIGNALED(*status))
	{
		g_data.exit_status = 128 + WTERMSIG(*status);
		if (WTERMSIG(*status) == SIGINT)
			printf("\n");
		if (WTERMSIG(*status) == SIGQUIT)
			printf("\n");
	}
}

void	clean_all_exit(char *str, int nb)
{
	clean_all(str, nb);
	exit(nb);
}
