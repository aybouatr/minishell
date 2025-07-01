/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helpers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 19:28:21 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/11 19:43:28 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	skip_all_word(char *str, int i)
{
	if (str[i] == '?')
		i++;
	else
		while (str[i] && ft_isalpha(str[i]))
			i++;
	return (i);
}

t_token	*check_names_token(t_token *temp)
{
	t_token			*token;
	t_type_token	type;

	token = temp;
	type = e_nothin;
	while (temp)
	{
		temp->type_token = get_type_token(type, temp->content);
		type = temp->type_token;
		temp = temp->next;
	}
	return (token);
}
