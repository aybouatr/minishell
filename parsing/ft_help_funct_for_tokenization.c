/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_help_funct_for_tokenization.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:30:43 by aybouatr          #+#    #+#             */
/*   Updated: 2025/03/20 01:30:46 by aybouatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*sstrdup(const char *s)
{
	size_t	i;
	char	*p;

	i = ft_strlen(s);
	p = (char *)allocation((i + 1));
	i = 0;
	while (s && s[i])
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	check_quote(t_quote *ifo_quote, char c)
{
	if (c != '\'' && c != '"')
		return ;
	if (ifo_quote->status_quote == e_close)
	{
		if (c == '\'')
		{
			ifo_quote->type_quote = e_single_quote;
			ifo_quote->status_quote = e_open;
		}
		else if (c == '"')
		{
			ifo_quote->type_quote = e_double_quote;
			ifo_quote->status_quote = e_open;
		}
	}
	else if (ifo_quote->status_quote == e_open)
	{
		if ((ifo_quote->type_quote == e_single_quote && c == '\'')
			|| (ifo_quote->type_quote == e_double_quote && c == '"'))
		{
			ifo_quote->type_quote = e_nothing;
			ifo_quote->status_quote = e_close;
		}
	}
}

void	insilize_quote(t_quote *quote)
{
	quote->status_quote = e_close;
	quote->type_quote = e_nothing;
}

void	skip_token(char **str)
{
	if (*str[0] == '<' && str[0][1] == '<')
	{
		(*str) += 2;
		return ;
	}
	if (*str[0] == '>' && str[0][1] == '>')
	{
		(*str) += 2;
		return ;
	}
	if (*str[0] == '|')
	{
		(*str) += 1;
		return ;
	}
	if (*str[0] == '<')
	{
		(*str) += 1;
		return ;
	}
	(*str) += 1;
	return ;
}

void	assign_name_to_token(char **tokens, t_token **list)
{
	t_token			*lst_token;
	t_token			*temp;
	int				i;
	e_type_token	typ_token;

	i = -1;
	lst_token = NULL;
	temp = NULL;
	typ_token = e_nothin;
	while (tokens && tokens[++i])
		ft_tokenadd_back(&temp, ft_tokennew(tokens[i]));
	lst_token = temp;
	while (lst_token && lst_token)
	{
		lst_token->type_token = get_type_token(typ_token, lst_token->content);
		typ_token = lst_token->type_token;
		lst_token = lst_token->next;
	}
	*list = temp;
}
