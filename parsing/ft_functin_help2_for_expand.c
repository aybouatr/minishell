/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functin_help2_for_expand.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybouatr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 18:42:02 by aybouatr          #+#    #+#             */
/*   Updated: 2025/05/07 18:42:05 by aybouatr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	condition_exp(char *str, int i, t_quote quote)
{
	if (quote.type_quote != e_single_quote && str[i] == '$'
		&& (ft_isalpha(str[i + 1]) || str[i + 1] == '?'))
		return (1);
	return (0);
}

char	**get_values_the_keys(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
	{
		if (ft_strncmp(arr[i], "?", 1) == 0)
		{
			arr[i] = ft_strjoin_gc(ft_itoa_grbg(g_data.exit_status),
					&arr[i][1]);
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
		if (str[i] == '$' && (ft_isalpha(str[i + 1]) || str[i + 1] == '?'))
		{
			index_value = 0;
			i = skip_all_word(str, i + 1);
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
	char	**arr_w;

	int (i), (j), (i_w);
	arr_w = (char **)allocation_2d(count_wrd_expand(str) + 1);
	i_w = 0;
	i = 0;
	while (str && str[++i] != '\0')
	{
		if (str[i - 1] == '$' && (ft_isalpha(str[i]) || str[i] == '?'))
		{
			j = 0;
			arr_w[i_w] = (char *)allocation(len_key_expand(&str[i]) + 1);
			if (str[i] == '?')
				i++;
			if (str[i - 1] == '?')
				arr_w[i_w++] = ft_strdup_env("?");
			else
			{
				while (str[i] && ft_isalpha(str[i]))
					arr_w[i_w][j++] = str[i++];
				arr_w[i_w++][j] = '\0';
			}
		}
	}
	return (arr_w[i_w] = NULL, remplace_keys_to_values_here_doc(str, arr_w));
}

char	*get_value_from_env(char *key)
{
	char	**env;
	int		index_key;

	index_key = 0;
	env = g_data.env;
	while (env && env[index_key])
	{
		if (!ft_strncmp(env[index_key], key, ft_strlen(key)) && env[index_key][ft_strlen(key)] == '=')
			return (sstrdup(&env[index_key][ft_strlen(key) + 1]));
		index_key++;
	}
	return (sstrdup(""));
}
