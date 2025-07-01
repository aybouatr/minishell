/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 19:25:03 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/10 18:01:34 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	input_redirection(t_2d_list *tokens)
{
	int	fd;

	fd = open(tokens->content[1], O_RDONLY);
	if (fd == -1)
	{
		perror((char *)tokens->content[1]);
		return (-1);
	}
	if (dup2(fd, 0) == -1)
	{
		printf("the dup2 has faild\n");
		return (-1);
	}
	close(fd);
	return (1);
}

int	output_redirection(t_2d_list *tokens)
{
	int	fd;

	fd = open(tokens->content[1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		dup_intializer();
		perror((char *)tokens->content[1]);
		g_data.exit_status = EXIT_FAILURE;
		return (-1);
	}
	if (dup2(fd, 1) == -1)
	{
		printf("the dup2 has faild\n");
		return (-1);
	}
	close(fd);
	return (1);
}

t_2d_list	*for_multiple_rediapp(t_2d_list **tokens)
{
	t_2d_list	*redirect_list;
	t_2d_list	*current;

	redirect_list = NULL;
	current = *tokens;
	while (current && current->next && current->next->type_token == e_redir_app)
	{
		if (!redirect_list)
			redirect_list = current->next;
		current = current->next->next;
	}
	return (redirect_list);
}

int	append_redirection(t_2d_list *tokens)
{
	int	fd;

	fd = open(tokens->content[1], O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd == -1)
	{
		perror((char *)tokens->content[1]);
		g_data.exit_status = EXIT_FAILURE;
		return (-1);
	}
	if (dup2(fd, 1) == -1)
	{
		printf("the dup2 has faild\n");
		return (-1);
	}
	close(fd);
	return (1);
}

int	exit_status(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (status);
}
