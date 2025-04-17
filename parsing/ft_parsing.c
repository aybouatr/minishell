/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:28:53 by aybouatr          #+#    #+#             */
/*   Updated: 2025/03/20 01:28:56 by aybouatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_opertor_or_redire(t_token *token)
{
	if (!token)
		return (1);
	if (token->type_token != e_arg && token->type_token != e_name_file
		&& token->type_token != e_delimeter_here_doc)
		return (1);
	return (0);
}

int	len_not_oper_redir(t_token *pos)
{
	int	counter;

	counter = 1;
	if (pos)
		pos = pos->next;
	while (!is_opertor_or_redire(pos))
	{
		pos = pos->next;
		counter++;
	}
	return (counter);
}

void	split_token_to_opertor(t_token *Head, t_2d_list **lst_token)
{
	t_2d_list	*lst;
	void		**arr;
	int			nbr_argm;
	int			i;

	lst = NULL;
	while (Head)
	{
		i = 0;
		nbr_argm = len_not_oper_redir(Head);
		arr = allocation_2d(nbr_argm + 1);
		arr[i++] = Head->content;
		Head = Head->next;
		while (!is_opertor_or_redire(Head))
		{
			arr[i++] = Head->content;
			Head = Head->next;
		}
		arr[i] = NULL;
		ft_lstadd_2d_back(&lst, ft_2d_lstnew(arr));
	}
	*lst_token = lst;
}

t_2d_list	*rename_tokents(t_2d_list *lst_t, t_token *list)
{
	t_2d_list	*lst;

	lst = lst_t;
	while (list)
	{
		if (is_opertor_or_redire(list))
		{
			if (is_builts(list->content))
				lst_t->type_token = e_builtins;
			else
				lst_t->type_token = list->type_token;
			lst_t = lst_t->next;
		}
		list = list->next;
	}
	return (lst);
}

int	ft_parsing(char *str, t_2d_list **lst_tok)
{
	t_l			*head;
	t_token		*list;
	char		**tokens;
	t_2d_list	*lst_token;
	int			i;

	list = NULL;
	i = 0;
	tokens = split_to_token(str, &head);
	if (!tokens)
		return (1);
	assign_name_to_token(tokens, &list);
	if (1 == ft_grammer(list))
		return (1);
	hand_quote(&list);
	ft_expand(&list, head);
	split_token_to_opertor(list, &lst_token);
	lst_token = rename_tokents(lst_token, list);
	*lst_tok = lst_token;
	return (0);
}
