/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:18:47 by oachbani          #+#    #+#             */
/*   Updated: 2025/04/03 16:27:38 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path()
{
	while (*g_data.env)
	{
		if (ft_strncmp(*g_data.env, "PATH=", 5) == 0)
			return (*g_data.env + 5);
		g_data.env++;
	}
	return (NULL);
}

char	*ft_checkfirst(char *str)
{
	if (access(str, X_OK) == 0)
		return (str);
	return (NULL);
}


char	*ft_check(char *str, char *path)
{
	char	**parse;
	char	*s;
	int		i;
	char	*nstr;

	i = 0 ;
	parse = ft_split(path, ':');
	if (!parse || str[0] == '/' || str[0] == '.' || !str[0])
	{
		ft_free(parse);
		return (NULL);
	}
	nstr = ft_strjoin("/", str);
	while (parse[i])
	{
		s = ft_strjoin(parse[i], nstr);
		if (access(s, X_OK) == 0)
			return (s);
		free(s);
		i++;
	}
	ft_free(parse);
	return (free(nstr), NULL);
}


