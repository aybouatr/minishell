/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functin_help_for_expand.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:29:16 by aybouatr          #+#    #+#             */
/*   Updated: 2025/05/10 10:52:13 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

	if (!str)
		return (0);
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
