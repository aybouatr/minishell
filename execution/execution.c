/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 14:58:54 by oachbani          #+#    #+#             */
/*   Updated: 2025/04/19 17:52:05 by oachbani         ###   ########.fr       */
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
	
	fd = open(tokens->content[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
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
t_2d_list	*for_multiple_rediapp(t_2d_list **tokens)
{
    t_2d_list *redirect_list = NULL;
    t_2d_list *current = *tokens;

    while (current && current->next && current->next->type_token == e_redir_app)
    {
        if (!redirect_list)
            redirect_list = current->next;
        current = current->next->next;
    }
    return(redirect_list);
}

int append_redirection(t_2d_list *tokens)
{
    int fd;
    
    fd = open(tokens->content[1], O_CREAT | O_RDWR | O_APPEND, 0644);
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

int	work_with_pipe(int *status, t_2d_list **tokens)
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
		execute_command(*tokens);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], 0);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	(*tokens) = (*tokens)->next->next;
	return(exit_status(*status));
}

void	 error(int i)
{
	ft_putstr_fd("Error ", 2);
	g_data.exit_status = 1;
}

void	waitforchild(pid_t pid , int *status)
{
	if (waitpid(pid, status, 0) == -1)
	{
		printf("minishell : waitpidfailed\n");
		g_data.exit_status = EXIT_FAILURE;
	}
}

void	apply_builtin_forked(t_2d_list *tokens)
{
	if (ft_strcmp(tokens->content[0],"export") == 0)
	{
		re_export((char **)tokens->content);
		exit(g_data.exit_status);
	}
	if (ft_strcmp(tokens->content[0],"env") == 0)
	{
		re_env();
		exit(g_data.exit_status);
	}
}

int	apply_builtin(t_2d_list *tokens)
{
	if (ft_strcmp(tokens->content[0],"pwd") == 0)
		re_pwd();
	if (ft_strcmp(tokens->content[0],"cd") == 0)
	{
		if (tokens->content[2])
			return(printf("minishell : cd: too many arguments\n"), 1);
		re_cd(tokens->content[1]);
		return(1);
	}
	if (ft_strcmp(tokens->content[0],"echo") == 0)
		re_echo(tokens->content);
	if (ft_strcmp(tokens->content[0],"env") == 0)
		re_env();
	if (ft_strcmp(tokens->content[0],"unset") == 0)
		re_unset(tokens->content);
	if (ft_strcmp(tokens->content[0],"exit") == 0)
		re_exit(tokens->content);
	if (ft_strcmp(tokens->content[0],"export") == 0)
		re_export(tokens->content);
	return(0);
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
	return(0);
}

t_2d_list	*for_multiple_rediou(t_2d_list **tokens)
{
	t_2d_list *redirect_list = NULL;
    t_2d_list *current = *tokens;

    while (current && current->next && current->next->type_token == e_redir_ou)
    {
        if (!redirect_list)
            redirect_list = current->next;
        current = current->next->next;
	}
	return(redirect_list);
}

void	open_skip(t_2d_list *files, t_2d_list **tokens)
{
    while (files)
    {
        if (files->type_token == e_redir_ou)
        {
            if (!output_redirection(files))
                clean_memory("minishell : failed to open file\n", 1);
            if (files->next && (files->next->type_token == e_redir_ou || 
                             files->next->type_token == e_redir_app))
                files = files->next;
            else
                break;
        }
        else if (files->type_token == e_redir_app)
        {
            if (!append_redirection(files))
                clean_memory("minishell : failed to open file\n", 1);
            if (files->next && (files->next->type_token == e_redir_ou || 
                             files->next->type_token == e_redir_app))
                files = files->next;
            else
                break;
        }
        else
            break;
    }	
}

int execution_machine(t_2d_list **tokens)
{
	pid_t	pid;
	int		status;
	t_2d_list *files;
	t_2d_list *filesapp;
	
	files = for_multiple_rediou(tokens);
	filesapp = for_multiple_rediapp(tokens);
	if ((*tokens)->type_token == e_builtins)
	{
		apply_builtin(*tokens);
		return (0);
	}
	pid = fork();
	if (pid == 0)
	{
		if (files)
			open_skip(files, tokens);
		else if (filesapp)
			open_skip(filesapp, tokens);
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

	apply_builtin_forked(tokens);
	path = get_path(g_data.env);
	if (!path && !ft_checkfirst(tokens->content[0]))
	{
		dup_intializer();
		printf("%s : command not found\n", (char *)tokens->content[0]);
		exit(127);
	}
	if (!ft_checkfirst(tokens->content[0]))
		exe = ft_check(tokens->content[0], path);
	else
		exe = ft_checkfirst(tokens->content[0]);
	if (!exe)
	{
		dup_intializer();
		printf("%s : command not found\n", (char *)tokens->content[0]);
		exit(127);
	}
	execve(exe, (char **)tokens->content, g_data.env);
	printf("minishell : ../: Is a directory\n");
	exit(126);
}

void dup_intializer(void)
{
	dup2(g_data.or_stdin, 0);
    dup2(g_data.or_stdout, 1);
    close(g_data.or_stdin);
    close(g_data.or_stdout);
}

void	next_one(t_2d_list **tokens)
{
	if ((*tokens)->next && (*tokens)->next->type_token == e_redir_ou)
            while((*tokens) && (*tokens)->next && (*tokens)->next->type_token == e_redir_ou)
                (*tokens) = (*tokens)->next->next;
	else if ((*tokens)->next && (*tokens)->next->type_token == e_redir_app)
			while((*tokens) && (*tokens)->next && (*tokens)->next->type_token == e_redir_app)
				(*tokens) = (*tokens)->next->next;
	else if ((*tokens)->next && (*tokens)->next->type_token == e_here_doc)
			while((*tokens) && (*tokens)->next && (*tokens)->next->type_token == e_here_doc)
				(*tokens) = (*tokens)->next->next;
    else
    	(*tokens) = (*tokens)->next;
}

int	ft_next_check(t_2d_list *tokens)
{
	// if (!tokens->next &&tokens->type_token == e_redir_ou )
	// 	output_redirection(tokens);
	if(!tokens->next && (tokens->type_token == e_redir_in ||\
		tokens->type_token == e_redir_app || tokens->type_token == e_redir_ou))
		return(0);
	if (!tokens->next && tokens->type_token == e_here_doc)
		return(0);
	return (1);
}

int		check_ifquoted(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return(0);
}
int	cold_arms(char *line, char *limiter)
{
	char	*join;
	
	join = ft_strjoin(limiter , "\n");
	
	if (ft_strncmp(join, \
			line, ft_strlen(limiter) + 1) == 0)
	{
		free(join);
		return(2);
	}
	free(join);
	return (0);
}

char	*add_nl(char *str)
{
	char	*join;

	join =  ft_strjoin_gc(str, "\n");
	return(join);
}

char	*del_nl(char *str)
{
	int	len;

	len = ft_strlen(str) - 1 ;
	if (str[len] == '\n')
		str[len] = '\0';
	return(str);
}

void	for_norm(int check, char **line , char **new)
{
	if (check != 1)
	{
		*line = del_nl(*line);
		*new = get_arg_expand_for_here_doc(*line);
		*new = add_nl(*new);
	}
	else
		*new = *line;
}

// void	ft_here_doc(char *limiter, t_2d_list *tokens)
// {
// 	char	*line;
// 	pid_t	pid;
// 	int		check;
// 	char	*new;

// 	int fd = open("/tmp/here_doc", O_CREAT | O_RDWR | O_TRUNC , 0644);
// 	check = check_ifquoted(limiter);
// 	limiter = delete_quote(limiter);
// 	line = get_next_line(0);
// 	while (1)
// 	{
// 		for_norm(check, &line, &new);
// 		if (cold_arms(new, limiter) == 2)
// 			break;
// 		write(fd, new, ft_strlen(new));
// 		free(line);
// 		line = get_next_line(0);
// 	}
// 	free(line);
// 	exit(EXIT_SUCCESS);
// }

void handle_heredoc(pid_t pid , int status)
{
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		g_data.exit_status = EXIT_SUCCESS;
		if (WEXITSTATUS(status))
		{
			g_data.exit_status = EXIT_FAILURE;
			return ;
		}
	}
}

void	apply_here_doc(t_2d_list *tokens)
{
	t_2d_list *current;
	pid_t pid;
	int	status;

	current = tokens;
	if (tokens && tokens->type_token == e_here_doc)
	{
		int fd = open("/tmp/here_doc", O_CREAT | O_RDWR | O_TRUNC , 0644);
		pid = fork();
		if (pid == 0)
			ft_here_doc(tokens->content[1], tokens);
		else
			handle_heredoc(pid, status);
		dup2(fd, 0);
	}
	while(current && current->next && current->next->type_token == e_here_doc)
	{
		int fd = open("/tmp/here_doc", O_CREAT | O_RDWR | O_TRUNC , 0644);
		pid = fork();
		if (pid == 0)
			ft_here_doc(tokens->next->content[1], tokens);
		else
			handle_heredoc(pid, status);
		dup2(fd, 0);
		current = current->next;
	}
}

void	start_execution(t_2d_list *tokens)
{
	int status;

	status = 0;
	g_data.or_stdin = dup(0);
    g_data.or_stdout = dup(1);
	while(tokens)
	{
		if (input_redi(&tokens) == 10)
				break;
		apply_here_doc(tokens);
		if (tokens->next && tokens->next->type_token == e_pipe)
		{
			work_with_pipe(&status, &tokens);
			continue;
		}
		if(!ft_next_check(tokens))
			break;
		g_data.exit_status = execution_machine(&tokens);
		while(wait(NULL) > 0)
			;
		next_one(&tokens);
	}
	dup_intializer();
}
