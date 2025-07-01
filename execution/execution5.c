/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:33:00 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/11 19:35:39 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_2d_list	*get_builtin(t_2d_list *tokens)
{
	t_2d_list	*builtin;

	builtin = NULL;
	while (tokens && tokens->type_token != e_pipe)
	{
		if (tokens->type_token == e_builtins)
		{
			builtin = tokens;
			return (builtin);
		}
		tokens = tokens->next;
	}
	return (NULL);
}

void	signal_handler(void)
{
	write(1, "\n", 1);
	clean_all("", 2);
	exit(2);
}

int	execution_machine(t_2d_list **tokens)
{
	pid_t	pid;
	int		status;

	status = 0;
	if (!tokens || !(*tokens))
		return (0);
	if (get_builtin(*tokens) && g_data.pipe == NO)
		return (for_builtin(get_builtin(*tokens)));
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	pid = fork();
	if (pid == 0)
	{
		if (apply_redirection(*tokens) == -1)
			clean_all_exit("", 1);
		skip_no_cmd(tokens);
		execute_command(*tokens);
	}
	else if (pid > 0)
		waitforchild(pid, &status);
	return (exit_status(status));
}

void	clean_all(char *str, int i)
{
	clean_memory(str, i);
	clean_env();
}

void	execute_command(t_2d_list *tk)
{
	char *(exe), *(path);
	if (!tk || !tk->content || !tk->content[0])
		return (clean_all("", g_data.exit_status), exit(g_data.exit_status));
	apply_builtin_forked(tk);
	path = get_path(g_data.env);
	if (!path && !ft_checkfirst(tk->content[0]))
	{
		dup_intializer();
		printf("minishell: %s: Permission denied\n", (char *)tk->content[0]);
		clean_all("", 126);
		exit(126);
	}
	if (!ft_checkfirst(tk->content[0]))
		exe = ft_check(tk->content[0], path);
	else
		exe = ft_checkfirst(tk->content[0]);
	if (!exe)
	{
		dup_intializer();
		printf("%s : command not found\n", (char *)tk->content[0]);
		return (clean_all("", 127), exit(127));
	}
	execve(exe, (char **)tk->content, g_data.env);
	return (clean_all("", 126), exit(126));
}
