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

int is_redir(t_2d_list* lst)
{
	if (lst && (lst->type_token == e_redir_app || lst->type_token == e_here_doc || lst->type_token == e_redir_ou || lst->type_token == e_redir_in))
		return (1);
	return (0);
}

int is_next_redir_and_next_next_arg(t_2d_list* lst)
{
	if (lst && is_redir(lst) && lst->next && lst->next->type_token == e_cmd)
		return (1);
	return (0);
}

char** str_joine_2d(char** arr1,char** arr2)
{
	int counter1;
	int counter2;
	int i;
	char** new_arr;

	counter1 = 0;
	counter2 = 0;
	i = 0;
	while (arr1 && arr1[counter1])
		counter1++;
	while (arr2 && arr2[counter2])
		counter2++;
	new_arr = allocation_2d((counter1 + counter2 + 1));
	counter1 = 0;
	counter2 = 0;
	while (arr1 && arr1[counter1])
		new_arr[i++] = arr1[counter1++];
	while (arr2 && arr2[counter2])
		new_arr[i++] = arr2[counter2++];
	new_arr[i] = NULL;
	return (new_arr);
}

t_2d_list* deplacement_arg_near_cmd(t_2d_list* lst_token)
{
	t_2d_list* temp;
	t_2d_list* head;
	char**     save_arg;
	int check;

	temp = lst_token;
	head =    temp;
	check = 0;
	while (temp)
	{
		if ( temp->next && temp->type_token == e_cmd && is_next_redir_and_next_next_arg(temp->next))
		{
			temp->content = str_joine_2d(temp->content,temp->next->next->content);
			temp->next->next = temp->next->next->next;
			temp = temp->next->next;
		}
		else
			temp = temp->next;
	}
	return (head);
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
	//ft_expend_spicifique_cases(list,head);
	//hand_quote(&list);
	ft_expand(&list, head);
	split_token_to_opertor(list, &lst_token);
	lst_token = rename_tokents(lst_token, list);
	lst_token = deplacement_arg_near_cmd(lst_token);
	*lst_tok = lst_token;
	return (0);
}
