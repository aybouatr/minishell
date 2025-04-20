/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functin_help_for_expand.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:29:16 by aybouatr          #+#    #+#             */
/*   Updated: 2025/03/20 01:29:19 by aybouatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_need_expand(t_l *list, int i)
{
	while (list)
	{
		if (list->content == i)
			return (0);
		list = list->next;
	}
	return (1);
}

int	len_arr(char **arr, char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = 0;
	while (arr && arr[i])
	{
		len += ft_strlen(arr[i]);
		i++;
	}
	return (len);
}

int	count_wrd_expand(char *str)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	while (str[i])
	{
		if (str[i] && str[i] == '$' && str[i + 1] != '$')
			counter++;
		i++;
	}
	return (counter);
}

int	len_key_expand(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$' && !is_spaces(str[i]) && str[i] != '\''
		&& str[i] != '"')
		i++;
	return (i);
}

int	is_shoold_expand(t_quote quote, char c)
{
	if (quote.status_quote == e_open && quote.type_quote == e_single_quote
		&& c == '$')
		return (1);
	return (0);
}
