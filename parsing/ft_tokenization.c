/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:30:15 by aybouatr          #+#    #+#             */
/*   Updated: 2025/05/11 19:43:28 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_nbr_token(char *str, int *counter, t_l **head)
{
	short	check;
	t_quote	quote;

	insilize_quote(&quote);
	while (str && *str)
	{
		check = 0;
		while (*str && is_spaces(*str))
			str++;
		if (*str && is_not_opertor(*str, quote) && (!is_spaces(*str)
				|| quote.status_quote == e_open))
			(*counter)++;
		str = process_token_with_quote(str, &quote, counter, &check);
		if (check == 1)
			ft_add_back(head, ft_new((*counter - 1)));
		if (!is_not_opertor(*str, quote))
		{
			skip_token(&str);
			(*counter)++;
		}
	}
	if (quote.status_quote == e_open)
		return (1);
	return (0);
}

char	*ft_operator_token(char **str)
{
	if (*str[0] == '<' && str[0][1] == '<')
	{
		(*str) += 2;
		return (sstrdup("<<"));
	}
	if (*str[0] == '>' && str[0][1] == '>')
	{
		(*str) += 2;
		return (sstrdup(">>"));
	}
	if (*str[0] == '|')
	{
		(*str) += 1;
		return (sstrdup("|"));
	}
	if (*str[0] == '<')
	{
		(*str) += 1;
		return (sstrdup("<"));
	}
	(*str) += 1;
	return (sstrdup(">"));
}

t_type_token	get_type_token(t_type_token prev, char *content)
{
	if (!ft_strcmp(content, "<"))
		return (e_redir_in);
	if (!ft_strcmp(content, "<<"))
		return (e_here_doc);
	if (!ft_strcmp(content, ">>"))
		return (e_redir_app);
	if (!ft_strcmp(content, "|"))
		return (e_pipe);
	if (!ft_strcmp(content, ">"))
		return (e_redir_ou);
	if (prev == e_here_doc)
		return (e_delimeter_here_doc);
	if (prev == e_redir_app || prev == e_redir_in || prev == e_redir_ou)
		return (e_name_file);
	if (prev == e_arg || prev == e_cmd)
		return (e_arg);
	return (e_cmd);
}

char	*get_token(t_quote *quot, char **input_line)
{
	t_quote	quote;
	char	word[1000];
	int		i;

	quote = *quot;
	i = 0;
	if (!is_not_opertor(**input_line, quote))
		return (ft_operator_token(input_line));
	while (**input_line && is_not_opertor(**input_line, quote)
		&& (!is_spaces(**input_line) || quote.status_quote == e_open))
	{
		check_quote(&quote, **input_line);
		word[i++] = *(*input_line)++;
	}
	word[i] = '\0';
	*quot = quote;
	return (sstrdup(word));
}

char	**split_to_token(char *input_line, t_l **head)
{
	t_l		*h_ead;
	char	**arr;
	t_quote	quote;

	int (token_count), (token_index);
	h_ead = NULL;
	token_index = 0;
	token_count = 0;
	insilize_quote(&quote);
	if (1 == count_nbr_token(input_line, &token_count, &h_ead))
		return (clean_memory("parsing quote\n", 1), NULL);
	arr = (char **)allocation_2d((token_count + 1));
	while (input_line && *input_line)
	{
		while (*input_line && is_spaces(*input_line))
			input_line++;
		if (*input_line)
			arr[token_index++] = get_token(&quote, &input_line);
	}
	arr[token_index] = NULL;
	*head = h_ead;
	return (arr);
}
