/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:10:44 by aybouatr          #+#    #+#             */
/*   Updated: 2025/05/11 19:22:25 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redir(t_2d_list *lst)
{
	if (lst && (lst->type_token == e_redir_app || lst->type_token == e_here_doc
			|| lst->type_token == e_redir_ou || lst->type_token == e_redir_in))
		return (1);
	return (0);
}

char	**str_joine_2d(char **arr1, char **arr2)
{
	int		counter1;
	int		counter2;
	int		i;
	char	**new_arr;

	counter1 = 0;
	counter2 = 0;
	i = 0;
	while (arr1 && arr1[counter1])
		counter1++;
	while (arr2 && arr2[counter2])
		counter2++;
	new_arr = (char **)allocation_2d((counter1 + counter2 + 1));
	counter1 = 0;
	counter2 = 0;
	while (arr1 && arr1[counter1])
		new_arr[i++] = arr1[counter1++];
	while (arr2 && arr2[counter2])
		new_arr[i++] = arr2[counter2++];
	new_arr[i] = NULL;
	return (new_arr);
}

void	**get_all_arg_then_pipe(t_2d_list *l)
{
	void		**arr;
	t_2d_list	*lst;

	lst = l;
	arr = NULL;
	while (lst && lst->type_token != e_pipe)
	{
		if (lst && (lst->type_token == e_cmd || lst->type_token == e_builtins))
			arr = (void **)str_joine_2d((char **)arr, (char **)lst->content);
		lst = lst->next;
	}
	return (arr);
}

t_2d_list	*skip_tokens(t_2d_list *temp)
{
	t_2d_list	*stock_temp;

	stock_temp = temp;
	if (temp && temp->next && (temp->next->type_token == e_cmd
			|| temp->next->type_token == e_builtins))
		temp = temp->next->next;
	else
		temp = temp->next;
	stock_temp->next = temp;
	stock_temp = stock_temp->next;
	temp = stock_temp;
	return (stock_temp);
}

t_2d_list	*deplacement_arg_near_cmd(t_2d_list *lst_token)
{
	t_2d_list	*temp;
	t_2d_list	*head;

	temp = lst_token;
	head = temp;
	while (temp)
	{
		if (temp && (temp->type_token == e_cmd
				|| temp->type_token == e_builtins))
			temp->content = get_all_arg_then_pipe(temp);
		if (temp && (temp->type_token == e_cmd
				|| temp->type_token == e_builtins))
		{
			temp = temp->next;
			while (temp && temp->type_token != e_pipe)
				temp = skip_tokens(temp);
		}
		else
			temp = temp->next;
	}
	return (lst_token);
}
