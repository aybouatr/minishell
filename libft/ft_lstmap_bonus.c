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

/*#include <stdio.h>


void	*itter(void *p)
{
	char	*new;
	char	*str;

	str = (char *)p;
	new = ft_strdup(str);
	free(p);
	return ((void *)new);
}

void delete (void *s)
{
	free(s);
}


int	main(void)
{
	t_list	*s1;
	t_list	*s2;
	t_list	*s3;
	t_list	*s4;
	t_list	*s5;
	t_list	*lists;

	s1 = malloc(sizeof(t_list));
	s2 = malloc(sizeof(t_list));
	s3 = malloc(sizeof(t_list));
	s4 = malloc(sizeof(t_list));
	s5 = malloc(sizeof(t_list));
	s1->content = ft_strdup("string1");
	s1->next = s2;
	s2->content = ft_strdup("string2");
	s2->next = s3;
	s3->content = ft_strdup("string3");
	s3->next = s4;
	s4->content = ft_strdup("string4");
	s4->next = s5;
	s5->content = ft_strdup("string5");
	s5->next = NULL;
	lists = ft_lstmap(s1, *itter, delete);
	while(lists)
	{
		printf("%s\n", (char *)lists->content);
		lists = lists->next;
	}
	return (0);
}
*/