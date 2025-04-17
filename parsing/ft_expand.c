/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 01:27:05 by aybouatr          #+#    #+#             */
/*   Updated: 2025/03/20 01:27:08 by aybouatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_strjoin_grbg(char *s1,char* s2)
{
	size_t	i;
	char	*p;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup_env(s2));
	if (s1 && !s2)
		return (ft_strdup_env(s1));
	i = ft_strlen(s1) + ft_strlen(s2);
	p = allocation((i + 1) * sizeof(char));
	if (!p)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		p[i] = s1[i];
	while (s2[++j])
		p[i++] = s2[j];
	return (p);
}

char	**get_values_the_keys(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		if (ft_strncmp(arr[i], "?",1) == 0)
		{
			arr[i] = ft_strjoin_grbg(ft_itoa_grbg(g_data.exit_status),&arr[i][1]);
		}
		else
			arr[i] = get_value_from_env(arr[i]);
		i++;
	}
	return (arr);
}

char	*remplace_keys_to_values(char *str, char **arr)
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

char	*get_arg_expand(char *str)
{
	char	**arr_words;
	
	int (i), (j), (index_word);
	arr_words = (char **)allocation_2d(count_wrd_expand(str) + 1);
	index_word = 0;
	i = 0;
	while (str && str[++i] != '\0')
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
	return (remplace_keys_to_values(str, arr_words));
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
		if (!is_need_expand(head, i))
			i = i + 0;
		else if (lst_token->type_token != e_delimeter_here_doc)
			lst_token->content = get_arg_expand(lst_token->content);
		i++;
		lst_token = lst_token->next;
	}
	*lst_to = temp_token;
}
