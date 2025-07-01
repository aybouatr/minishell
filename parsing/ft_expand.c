/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:27:05 by aybouatr          #+#    #+#             */
/*   Updated: 2025/05/11 19:30:32 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remplace_keys_to_values(char *str, char **arr)
{
	char	*value;
	t_quote	quote;

	int (j), (i), (index_value), (k);
	arr = get_values_the_keys(arr);
	insilize_quote(&quote);
	value = (char *)allocation(len_arr(arr, str) + 1);
	i = 0;
	j = 0;
	k = 0;
	while (str && str[i])
	{
		check_quote(&quote, str[i]);
		if (condition_exp(str, i, quote))
		{
			i = skip_all_word(str, i + 1);
			index_value = 0;
			while (arr && arr[k] != NULL && arr[k][index_value] != '\0')
				value[j++] = arr[k][index_value++];
			k++;
		}
		else
			value[j++] = str[i++];
	}
	return (value[j] = '\0', value);
}

char	*get_word(char *str, int *index)
{
	char	*arr_words;
	int		j;
	int		i;

	if (!str)
		return (NULL);
	i = *index;
	j = 0;
	arr_words = (char *)allocation(len_key_expand(&str[i]) + 1);
	while (str[i] && ft_isalpha(str[i]))
		arr_words[j++] = str[i++];
	arr_words[j] = '\0';
	*index = i;
	return (arr_words);
}

char	*get_arg_expand(char *str)
{
	char	**arr_words;
	t_quote	quote;

	int (i), (index_word);
	arr_words = (char **)allocation_2d(count_wrd_expand(str) + 1);
	index_word = 0;
	i = 0;
	insilize_quote(&quote);
	check_quote(&quote, str[i]);
	while (str && str[i] && str[++i] != '\0')
	{
		if (quote.type_quote != e_single_quote && str[i - 1] == '$'
			&& (ft_isalpha(str[i]) || str[i] == '?'))
		{
			if (str[i] == '?')
				i++;
			if (str[i - 1] == '?')
				arr_words[index_word++] = ft_strdup_env("?");
			else
				arr_words[index_word++] = get_word(str, &i);
		}
		check_quote(&quote, str[i]);
	}
	arr_words[index_word] = NULL;
	return (remplace_keys_to_values(str, arr_words));
}

t_token	*deleted_null_term_expend(t_token *token)
{
	t_token	*temp;
	t_token	*temp_token;
	t_token	*stock;

	temp = token;
	temp_token = temp;
	while (temp_token && ((char *)temp_token->content)[0] == '\0')
		temp_token = temp_token->next;
	temp = temp_token;
	while (temp)
	{
		stock = temp;
		if (temp && temp->next && ((char *)temp->next->content)[0] == '\0')
			temp = temp->next->next;
		else
			temp = temp->next;
		stock->next = temp;
		stock = stock->next;
		temp = stock;
	}
	temp_token = check_names_token(temp_token);
	return (temp_token);
}

int	ft_expand(t_token **lst_to, t_l *head)
{
	t_token	*lst_tok;
	t_token	*temp_token;
	int		i;

	(void)head;
	lst_tok = *lst_to;
	temp_token = lst_tok;
	i = 0;
	while (lst_tok)
	{
		if (lst_tok->type_token != e_delimeter_here_doc)
			lst_tok->content = delete_quote(get_arg_expand(lst_tok->content));
		i++;
		lst_tok = lst_tok->next;
	}
	temp_token = deleted_null_term_expend(temp_token);
	*lst_to = temp_token;
	if (!temp_token)
		return (1);
	return (0);
}
