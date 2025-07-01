/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:31:11 by aybouatr          #+#    #+#             */
/*   Updated: 2025/05/07 11:32:02 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_add_back(t_l **lst, t_l *new)
{
	t_l	*temp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

t_l	*ft_new(int content)
{
	t_l	*node;

	node = (t_l *)allocation(sizeof(t_l));
	if (!node)
		return (NULL);
	node->content = content;
	node->next = NULL;
	return (node);
}

int	is_spaces(char c)
{
	return (c == ' ' || c == '\t');
}

char	*process_token_with_quote(char *str, t_quote *quote, int *counter,
		short *check)
{
	(void)counter;
	while (*str && is_not_opertor(*str, *quote) && (!is_spaces(*str)
			|| quote->status_quote == e_open))
	{
		check_quote(quote, *str);
		if ((*str == '$' && (*(str + 1) == '"' || *(str + 1) == '\''))
			|| is_shoold_expand(*quote, *str))
			*check = 1;
		str++;
	}
	return (str);
}

int	is_not_opertor(char c, t_quote quote)
{
	if ((c == '>' || c == '<' || c == '|') && quote.status_quote == e_close)
		return (0);
	return (1);
}
