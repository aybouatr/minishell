/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garammer_and_deleted_quote.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:29:52 by aybouatr          #+#    #+#             */
/*   Updated: 2025/05/10 11:33:40 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_sizetoken(t_token *head)
{
	size_t	count;

	count = 0;
	while (head)
	{
		count++;
		head = head->next;
	}
	return (count);
}

int	is_builts(char *str)
{
	if (ft_strlen(str) == 0)
		return (0);
	if (!ft_strcmp(str, "echo") || !ft_strcmp(str, "cd"))
		return (1);
	if (!ft_strcmp(str, "export" ) || !ft_strcmp(str, "pwd"))
		return (1);
	if (!ft_strcmp(str, "env") || !ft_strcmp(str, "unset"))
		return (1);
	if (!ft_strcmp(str, "exit"))
		return (1);
	return (0);
}

char	*delete_quote(char *str)
{
	char	quote;

	int (i), (j), (dol);
	i = 0;
	j = 0;
	dol = 0;
	quote = 'n';
	while (str && str[i])
	{
		if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\'')
			&& quote == 'n')
			dol = 1;
		else if ((str[i] == '"' || str[i] == '\'') && quote == 'n')
			quote = str[i];
		else if ((str[i] == '"' || str[i] == '\'') && (str[i] == quote
				|| str[i] == quote))
			quote = 'n';
		else
			str[j++] = str[i];
		i++;
	}
	str[j] = '\0';
	return (str);
}

void	hand_quote(t_token **list)
{
	t_token	*head_token;
	t_token	*temp_token;

	head_token = *list;
	temp_token = head_token;
	while (head_token)
	{
		if (head_token->type_token != e_delimeter_here_doc)
			head_token->content = delete_quote(head_token->content);
		head_token = head_token->next;
	}
	*list = temp_token;
}

int	ft_grammer(t_token *lst)
{
	if (lst && lst->type_token == e_pipe)
		return (clean_memory("parsing error\n", 1), 1);
	while (lst && lst->next)
	{
		if (lst->type_token == e_cmd && lst->next->type_token == e_cmd)
			return (clean_memory("parsing error\n", 1), 1);
		if (lst->type_token == e_pipe && lst->next->type_token == e_pipe)
			return (clean_memory("parsing error\n", 1), 1);
		if (lst->type_token == e_here_doc
			&& lst->next->type_token != e_delimeter_here_doc)
			return (clean_memory("parsing error\n", 1), 1);
		if ((lst->type_token == e_redir_app || lst->type_token == e_redir_in
				|| lst->type_token == e_redir_ou)
			&& lst->next->type_token != e_name_file)
			return (clean_memory("parsing error\n", 1), 1);
		lst = lst->next;
	}
	if (lst)
		if ((lst->type_token == e_redir_app || lst->type_token == e_here_doc
				|| lst->type_token == e_redir_in
				|| lst->type_token == e_redir_ou || lst->type_token == e_pipe))
			return (clean_memory("parsing error\n", 1), 1);
	return (0);
}
