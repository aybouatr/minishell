/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:35:54 by oachbani          #+#    #+#             */
/*   Updated: 2024/11/07 18:56:59 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*p;
	t_list	*new;
	void	*tab;

	p = NULL;
	if (lst && f && del)
	{
		while (lst)
		{
			tab = f(lst -> content);
			new = ft_lstnew(tab);
			if (!new)
			{
				del(tab);
				ft_lstclear(&p, del);
				return (NULL);
			}
			ft_lstadd_back(&p, new);
			lst = lst->next;
		}
		return (p);
	}
	return (NULL);
}
