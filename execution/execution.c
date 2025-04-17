/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:58:54 by oachbani          #+#    #+#             */
/*   Updated: 2025/04/12 12:02:41 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../minishell.h"

int	input_redirection(t_2d_list *tokens)
{
	int	fd;
	
	fd = open(tokens->content[1], O_RDONLY);
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n", (char *)tokens->content[1]);
		g_data.exit_status = 0;
		return(0);
	}
	if (dup2(fd, 0) == -1)
	{
		printf("the dup2 has faild\n");
		return(0);
	}
	return (1);
}

int output_redirection(t_2d_list *tokens)
{
	int fd;

	fd = open(tokens->content[1], O_CREAT| O_RDWR | O_TRUNC, 0644);
	if(fd == -1)
	{
		printf("minishell : failed to open this file %s\n" , (char *)tokens->content[1]);
		g_data.exit_status = EXIT_FAILURE;
		return (0);
	}
	if (dup2(fd, 1) == -1)
	{
		printf("the dup2 has faild\n");
		return(0);
	}
	return (1);
}

int	exit_status(int status)
{
	if (WIFEXITED(status))
		return(WEXITSTATUS(status));
	return(status);
}

int	work_with_pipe(int *status, t_2d_list *tokens)
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
	{
		printf("minishell : pipe failed\n");
		g_data.exit_status = EXIT_FAILURE;
		return (0);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		execute_command(tokens);
	}
	else
	{
		waitforchild(pid, status);
		close(pipefd[1]);
		dup2(pipefd[0], 0);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	return(exit_status(*status));
}

void	 error(int i)
{
	ft_putstr_fd("Error ", 2);
	exit(i);
}

void	waitforchild(pid_t pid , int *status)
{
	if (waitpid(pid, status, 0) == -1)
	{
		printf("minishell : waitpidfailed\n");
		g_data.exit_status = EXIT_FAILURE;
	}
}

int	apply_builtin(t_2d_list *tokens)
{
	if (ft_strcmp(tokens->content[0],"pwd") == 0)
		return(re_pwd(), 1);
	if (ft_strcmp(tokens->content[0],"cd") == 0)
	{
		if (tokens->content[2])
			return(printf("minishell : cd: too many arguments\n"), 1);
		re_cd(tokens->content[1]);
		return(1);
	}
	if (ft_strcmp(tokens->content[0],"echo") == 0)
		return(re_echo(tokens->content), 1);
	if (ft_strcmp(tokens->content[0],"env") == 0)
		re_env();
	if (ft_strcmp(tokens->content[0],"unset") == 0)
		return(re_unset(tokens->content),1);
	if (ft_strcmp(tokens->content[0],"exit") == 0)
		return(re_exit(tokens->content), 1);
	if (ft_strcmp(tokens->content[0],"export") == 0)
		return(re_export(tokens->content),1);
	return(0);
}

void	input_redi(t_2d_list **tokens)
{
	if (!input_redirection((*tokens)))
		clean_memory("", 1);
	if ((*tokens)->next)
		(*tokens) = (*tokens)->next;
}

int execution_machine(t_2d_list **tokens)
{
	pid_t	pid;
	int		status;

	if ((*tokens)->type_token == e_builtins)
	{
		apply_builtin(*tokens);
		return (0);
	}
	pid = fork();
	if (pid == 0)
	{
		if ((*tokens)->next && (*tokens)->next->type_token == e_redir_ou)
			if (!output_redirection((*tokens)->next))
				clean_memory("minishell : failed to open file\n", 1);
			execute_command(*tokens);
	}
	else if (pid > 0)
		waitforchild(pid, &status);
	else
		clean_memory("minishell : fork just failed\n", 1);
	return(exit_status(status));
}

void	execute_command(t_2d_list *tokens)
{
	pid_t	pid;
	char	*path;
	char	*exe;

	path = get_path(g_data.env);
	if (!ft_check(tokens->content[0], path))
		exe = ft_checkfirst(tokens->content[0]);
	else
		exe = ft_check(tokens->content[0], path);
	if (!exe)
	{
		printf("%s : command not found\n", (char *)tokens->content[0]);
		clean_memory("", 127);
		return;
	}
	execve(exe, (char **)tokens->content, g_data.env);
	{
		printf("minishell : execve failed\n");
		clean_memory("", 126);
	}
}

void dup_intializer()
{
	int tty_fd = open("/dev/tty", O_RDONLY);
	dup2(tty_fd, STDOUT_FILENO);
	close(tty_fd);
}

// char *ft_here_doc()

void	start_execution(t_2d_list *tokens)
{
	int status;

	status = 0;
	int original_stdin = dup(0);
    int original_stdout = dup(1);
	while(tokens)
	{
		if (tokens->type_token == e_redir_in)
			input_redi(&tokens);
		if (tokens->next && tokens->next->type_token == e_pipe)
		{
			work_with_pipe(&status, tokens);
			tokens = tokens->next->next;
			continue;
		}
		if(!tokens->next && (tokens->type_token == e_redir_in || tokens->type_token == e_redir_ou))
			break;
		g_data.exit_status = execution_machine(&tokens);
		tokens = tokens->next;
	}
	dup2(original_stdin, 0);
    dup2(original_stdout, 1);
    close(original_stdin);
    close(original_stdout);
}
