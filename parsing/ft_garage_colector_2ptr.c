/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_garage_colector_2ptr.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:28:32 by aybouatr          #+#    #+#             */
/*   Updated: 2025/05/11 19:41:42 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	del(void *ptr)
{
	free(ptr);
	return ;
}

t_2d_list	*ft_2d_lstnew(void **conten)
{
	t_2d_list	*new;

	new = allocation(sizeof(t_2d_list));
	if (!new)
		return (NULL);
	new->content = conten;
	new->next = NULL;
	return (new);
}

void	ft_lstadd_2d_back(t_2d_list **lst, t_2d_list *new)
{
	t_2d_list	*temp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	temp = *lst;
	while (temp && temp->next)
		temp = temp->next;
	temp->next = new;
}

void	clean_memory_or_save_2d(void **ptr, t_status status)
{
	static t_2d_list	*save_add;

	if (status == save)
	{
		ft_lstadd_2d_back(&save_add, ft_2d_lstnew(ptr));
		return ;
	}
	if (status == clean)
	{
		while (save_add)
		{
			free(save_add->content);
			save_add = save_add->next;
		}
	}
}

void	**allocation_2d(size_t nbr_ptr)
{
	void	**ptr;

	ptr = malloc(nbr_ptr * sizeof(void *));
	if (!ptr)
		clean_memory("allocatio1n faild", 1);
	clean_memory_or_save_2d(ptr, save);
	return (ptr);
}
