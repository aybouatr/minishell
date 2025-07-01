/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:10:24 by aybouatr          #+#    #+#             */
/*   Updated: 2025/05/11 19:22:14 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_ifquoted(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	creat_file(char **temp)
{
	static int	nbr_file;
	char		*file_name;
	int			fd;

	nbr_file = 0;
	file_name = ft_strjoin_gc("/tmp/file", ft_itoa_grbg(nbr_file));
	file_name = ft_strjoin_gc(file_name, ".txt");
	nbr_file++;
	fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("minishell : failed to open this file %s\n", file_name);
		clean_memory("", 0);
		clean_env();
		g_data.exit_status = EXIT_FAILURE;
		return (-1);
	}
	*temp = file_name;
	return (fd);
}

void	ft_child_in_here_doc(int fd, char *limiter)
{
	int	check;

	char *(line), *(new);
	check = check_ifquoted(limiter);
	limiter = delete_quote(limiter);
	signal(SIGINT, set_child_signals);
	while (1)
	{
		line = get_next_line(0);
		if (!line || cold_arms(line, limiter) == 2)
			break ;
		for_norm(check, &line, &new);
		write(fd, new, ft_strlen(new));
		free(line);
		line = NULL;
	}
	close(fd);
	free(line);
	clean_memory("", 0);
	clean_env();
	exit(EXIT_SUCCESS);
}

char	*read_from_here_doc(char *limiter)
{
	pid_t	id_pro;
	char	*file;

	int (satus_child), (fd);
	signal(SIGINT, SIG_DFL);
	id_pro = fork();
	fd = creat_file(&file);
	if (id_pro == -1)
		return (clean_memory("faild fork", 1), clean_env(), exit(1), NULL);
	if (id_pro == 0)
	{
		ft_child_in_here_doc(fd, limiter);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(id_pro, &satus_child, 0);
	if (satus_child == 512)
	{
		g_data.exit_status = 130;
		g_data.sig_here_doc = 1;
	}
	return (file);
}

int	ft_here_doc(t_2d_list **lst_token)
{
	t_2d_list	*temp_lst;
	t_2d_list	*head_lst;

	temp_lst = *lst_token;
	head_lst = temp_lst;
	if (count_nbr_her_doc(*lst_token))
	{
		clean_all("minishell: maximum here-document count exceeded\n", 2);
		exit(2);
	}
	while (temp_lst && g_data.sig_here_doc == 0)
	{
		if (temp_lst->type_token == e_here_doc)
		{
			temp_lst->content[0] = read_from_here_doc(temp_lst->content[1]);
			temp_lst->content[1] = NULL;
		}
		temp_lst = temp_lst->next;
	}
	*lst_token = head_lst;
	setup_signals();
	return (g_data.sig_here_doc);
}
