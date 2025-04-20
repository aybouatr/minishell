/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:27:05 by aybouatr          #+#    #+#             */
/*   Updated: 2025/04/16 17:03:25 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**get_values_the_keys(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		if (ft_strncmp(arr[i], "?",1) == 0)
		{
			arr[i] = ft_strjoin_gc(ft_itoa_grbg(g_data.exit_status),&arr[i][1]);
		}
		else
			arr[i] = get_value_from_env(arr[i]);
		i++;
	}
	return (arr);
}

char	*remplace_keys_to_values_here_doc(char *str, char **arr)
{
	char	*value;

	int (j), (i), (index_value), (k);
	arr = get_values_the_keys(arr);
	value = (char *)allocation(len_arr(arr, str) + 1);
	i = 0;
	j = 0;
	k = 0;
	while (str && str[i])
	{
		if (str[i] == '$' && str[i + 1] != '\0' && str[i + 1] != '$' && str[i
				+ 1] != '\'' && !is_spaces(str[i + 1]))
		{
			i++;
			index_value = 0;
			while (str[i] && str[i] != '$' && str[i] != '\''
				&& !is_spaces(str[i]))
				i++;
			while (arr && arr[k] != NULL && arr[k][index_value] != '\0')
				value[j++] = arr[k][index_value++];
			k++;
		}
		else
			value[j++] = str[i++];
	}
	return (value[j] = '\0', value);
}

char	*get_arg_expand_for_here_doc(char *str)
{
	char	**arr_words;

	int (i), (j), (index_word);
	arr_words = (char **)allocation_2d(count_wrd_expand(str) + 1);
	index_word = 0;
	i = 0;
	while (str && str[++i] != '\0' )
	{
		if (str[i - 1] == '$' && str[i] != '$' && str[i] != '\''
			&& !is_spaces(str[i]))
		{
			j = 0;
			arr_words[index_word] = (char *)allocation(len_key_expand(&str[i])
					+ 1);
			while (str[i] && str[i] != '$' && str[i] != '"' && str[i] != '\''
				&& !is_spaces(str[i]))
				arr_words[index_word][j++] = str[i++];
			arr_words[index_word++][j] = '\0';
		}
	}
	arr_words[index_word] = NULL;
	return (remplace_keys_to_values_here_doc(str, arr_words));
}

char	*get_value_from_env(char *key)
{
	char	**env;
	int		index_key;

	index_key = 0;
	env = g_data.env;
	while (env && env[index_key])
	{
		if (!ft_strncmp(env[index_key], key, ft_strlen(key)))
			return (sstrdup(&env[index_key][ft_strlen(key) + 1]));
		index_key++;
	}
	return (sstrdup(""));
}

char	*remplace_keys_to_values(char *str, char **arr)
{
	char	*value;
	t_quote quote;

	int (j), (i), (index_value), (k);
	arr = get_values_the_keys(arr);
	insilize_quote(&quote);
	value = (char *)allocation(len_arr(arr, str) + 1);
	i = 0;
	j = 0;
	k = 0;
	while (str && str[i])
	{
		check_quote(&quote,str[i]);
		if (quote.type_quote != e_single_quote && str[i] == '$' && str[i  + 1] != '$' && str[i] != '\'' && str[i] != '"' && str[i + 1] != '\'' && str[i + 1] != '"' && !is_spaces(str[i]))
		{
			i++;
			index_value = 0;
			while (str[i] && str[i] != '$' && str[i] != '\'' && str[i] != '"'
				&& !is_spaces(str[i]))
				i++;
			while (arr && arr[k] != NULL && arr[k][index_value] != '\0')
				value[j++] = arr[k][index_value++];
			k++;
		}
		else
			value[j++] = str[i++];
	}
	if (str[i - 1] == '$')
		value[j++] = '$';
	return (value[j] = '\0', value);
}

char* get_arg_expand(char* str)
{
	char	**arr_words;
	t_quote quote;

	int (i), (j), (index_word);
	arr_words = (char **)allocation_2d(count_wrd_expand(str) + 1);
	index_word = 0;
	i = 0;
	insilize_quote(&quote);
	check_quote(&quote,str[i]);
	while (str && str[++i] != '\0' )
	{
		if (quote.type_quote != e_single_quote && str[i - 1] == '$'  &&  str[i] != '$' && str[i] != '\'' && str[i] != '"' && str[i + 1] != '\'' && str[i + 1] != '"' && !is_spaces(str[i]))
		{
			j = 0;
			arr_words[index_word] = (char *)allocation(len_key_expand(&str[i])
					+ 1);
			while (str[i] && str[i] != '$' && str[i] != '"' && str[i] != '\'' && !is_spaces(str[i]))
				arr_words[index_word][j++] = str[i++];
			arr_words[index_word++][j] = '\0';
		}
		check_quote(&quote,str[i]);
	}
	arr_words[index_word] = NULL;
	return (remplace_keys_to_values(str, arr_words));
}

void	ft_expand(t_token **lst_to, t_l *head)
{
	t_token	*lst_token;
	t_token	*temp_token;
	int		i;

	lst_token = *lst_to;
	temp_token = lst_token;
	i = 0;
	while (lst_token)
	{
		if (lst_token->type_token != e_delimeter_here_doc)
		{
			lst_token->content = delete_quote(get_arg_expand(lst_token->content));
		}
		i++;
		lst_token = lst_token->next;
	}
	*lst_to = temp_token;
}
