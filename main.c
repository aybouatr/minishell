/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:35:57 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/11 19:37:22 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

t_data	g_data;

void	handle_eof(void)
{
	clean_env();
	clean_memory("", 0);
	printf("exit\n");
	exit(g_data.exit_status);
}

void	handle_sigint(int sig)
{
	(void)sig;
	g_data.exit_status = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}

int	gc_free_one(void *ptr)
{
	t_list	*current;
	t_list	*prev;

	if (!ptr)
		return (0);
	prev = NULL;
	current = g_data.save_head_gc;
	while (current)
	{
		if (current->content == ptr)
		{
			if (prev)
				prev->next = current->next;
			else
				g_data.save_head_gc = current->next;
			free(current->content);
			free(current);
			return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

int	main(void)
{
	char		*line_input;
	t_2d_list	*lst_token;

	lst_token = NULL;
	start_env();
	setup_signals();
	while (1337)
	{
		g_data.sig_here_doc = 0;
		line_input = readline("-> minishell ");
		if (!line_input)
			handle_eof();
		else
			add_history(line_input);
		if (1 == ft_parsing(line_input, &lst_token))
			continue ;
		if (1 == handl_wildcards(&lst_token))
			continue ;
		start_execution(lst_token);
		clean_memory("", 0);
		free(line_input);
		line_input = NULL;
	}
}
