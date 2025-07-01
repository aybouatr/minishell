/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:39:18 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/11 19:34:10 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_nbr_her_doc(t_2d_list	*lst)
{
	int	counter;

	counter = 0;
	while (lst)
	{
		if (lst->type_token == e_here_doc)
			counter++;
		lst = lst->next;
	}
	if (counter > 16)
		return (1);
	return (0);
}

int	open_get_fd(t_2d_list *h_d)
{
	int	fd;

	if (h_d->type_token == e_here_doc)
		fd = open(h_d->content[0], O_RDONLY, 0644);
	else
		fd = open(h_d->content[1], O_RDONLY, 0644);
	if (fd == -1)
	{
		printf("%s: No such file or Directory \n", (char *)h_d->content[1]);
		return (-1);
	}
	dup2(fd, 0);
	return (0);
}

int	pipe_founder(t_2d_list *copy)
{
	t_2d_list	*tokens;

	tokens = copy;
	while (tokens && (tokens->type_token == e_here_doc
			|| tokens->type_token == e_redir_in || tokens->type_token == e_cmd))
		tokens = tokens->next;
	if (tokens && tokens->type_token == e_pipe)
		return (1);
	else
		return (0);
}

int	is_next_redir_and_next_next_arg(t_2d_list *lst)
{
	if (lst && is_redir(lst) && lst->next && lst->next->type_token == e_cmd)
		return (1);
	return (0);
}

void	dup_intializer(void)
{
	dup2(g_data.or_stdin, 0);
	dup2(g_data.or_stdout, 1);
}
