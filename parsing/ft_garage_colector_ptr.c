/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garage_colector_ptr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:28:09 by aybouatr          #+#    #+#             */
/*   Updated: 2025/05/11 19:41:42 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_tokenadd_back(t_token **lst, t_token *new)
{
	t_token	*current;

	if (!lst || !new)
		return ;
	current = (*lst);
	if (!current)
	{
		*lst = new;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = new;
}

t_token	*ft_tokennew(void *content)
{
	t_token	*head;

	head = (t_token *)allocation(sizeof(t_token));
	if (!head)
		return (NULL);
	head->content = content;
	head->next = NULL;
	return (head);
}

void	clean_memory_or_save(void *ptr, t_status status)
{
	static t_list	*save_add;

	if (status == save)
	{
		ft_lstadd_back(&save_add, ft_lstnew(ptr));
		return ;
	}
	if (status == clean)
		ft_lstclear(&save_add, del);
}

void	clean_memory(const char *meesage, int nb_exit)
{
	clean_memory_or_save_2d(NULL, clean);
	clean_memory_or_save(NULL, clean);
	if (nb_exit != 0)
		printf("%s", meesage);
}

void	*allocation(size_t nbr_byte)
{
	void	*ptr;

	ptr = malloc(nbr_byte);
	if (!ptr)
		clean_memory_or_save(ptr, clean);
	clean_memory_or_save(ptr, save);
	return (ptr);
}
