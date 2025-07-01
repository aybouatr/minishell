/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_grbg_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:19:40 by aybouatr          #+#    #+#             */
/*   Updated: 2025/05/11 19:41:42 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_2d_list	*ft_2d_lstnew_env(void **conten)
{
	t_2d_list	*new;

	new = (t_2d_list *)malloc(sizeof(t_2d_list));
	if (!new)
		return (NULL);
	new->content = conten;
	new->next = NULL;
	return (new);
}

char	*ft_itoa_grbg(int n)
{
	char	*p;

	long (i), (nbr);
	nbr = n;
	i = len(n);
	p = (char *)allocation((i + 1) * sizeof(char));
	if (!p)
		return (NULL);
	p[i] = '\0';
	if (nbr < 0)
	{
		p[0] = '-';
		nbr = -nbr;
	}
	else if (nbr == 0)
	{
		p[0] = '0';
		return (p);
	}
	while (nbr > 0)
	{
		p[--i] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (p);
}

void	clean_env_or_save(char *ptr, t_status status)
{
	static t_list	*save_add;

	g_data.save_head_gc = save_add;
	if (status == save)
	{
		ft_lstadd_back(&save_add, ft_lstnew(ptr));
		return ;
	}
	if (status == clean)
		ft_lstclear(&save_add, del);
}

void	clean_env_or_save_2d(char **ptr, t_status status)
{
	static t_2d_list	*save_add;
	t_2d_list			*temp;

	if (status == save)
	{
		ft_lstadd_2d_back(&save_add, ft_2d_lstnew_env((void **)ptr));
		return ;
	}
	if (status == clean)
	{
		while (save_add)
		{
			temp = save_add;
			save_add = save_add->next;
			free(temp->content);
			free(temp);
		}
	}
}

void	clean_env(void)
{
	free(g_data.cwd);
	clean_env_or_save(NULL, clean);
	clean_env_or_save_2d(NULL, clean);
}
