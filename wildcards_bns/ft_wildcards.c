/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wildcards.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 11:25:00 by aybouatr          #+#    #+#             */
/*   Updated: 2025/05/07 11:33:00 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*match_files(const char *pattern)
{
	struct dirent	*entry;
	t_token			*lst;
	DIR				*dp;

	dp = opendir(".");
	lst = NULL;
	if (dp == NULL)
		return (closedir(dp), NULL);
	while (1)
	{
		entry = readdir(dp);
		if (entry == NULL)
			break ;
		if (ft_fnmatch(pattern, entry->d_name) == 0)
			ft_tokenadd_back(&lst, ft_tokennew(grbc_strdup(entry->d_name)));
	}
	closedir(dp);
	return (lst);
}

int	is_found_wildcards(void **arr)
{
	int	index;

	index = 0;
	if (1 == len_arr((char **)arr, NULL))
		return (0);
	while (arr && arr[index])
	{
		if (ft_strchr(arr[index], '*'))
			return (1);
		index++;
	}
	return (0);
}

char	**copy_lst_into_arr(t_token *lst)
{
	int		index;
	t_token	*temp;
	char	**arr;

	index = 0;
	temp = lst;
	while (temp)
	{
		index++;
		temp = temp->next;
	}
	arr = (char **)allocation_2d((index + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	index = 0;
	temp = lst;
	while (temp)
	{
		arr[index] = grbc_strdup(temp->content);
		index++;
		temp = temp->next;
	}
	arr[index] = NULL;
	return (arr);
}

void	**processing_wildcards(char **arr)
{
	int		index;
	t_token	*stock;
	t_token	*lst_arr;

	index = 1;
	stock = NULL;
	ft_tokenadd_back(&stock, ft_tokennew(arr[0]));
	while (arr && arr[index])
	{
		lst_arr = match_files(arr[index]);
		while (lst_arr)
		{
			ft_tokenadd_back(&stock, ft_tokennew(lst_arr->content));
			lst_arr = lst_arr->next;
		}
		lst_arr = NULL;
		index++;
	}
	return ((void **)copy_lst_into_arr(stock));
}

int	handl_wildcards(t_2d_list **lst_token)
{
	t_2d_list	*lst;
	t_2d_list	*temp;

	lst = *lst_token;
	temp = lst;
	while (temp)
	{
		if ((temp->type_token == e_cmd || temp->type_token == e_builtins)
			&& is_found_wildcards(temp->content))
			temp->content = processing_wildcards((char **)temp->content);
		if (temp->content == NULL)
			return (clean_memory("no matches found\n", 1), 1);
		temp = temp->next;
	}
	*lst_token = lst;
	return (0);
}
