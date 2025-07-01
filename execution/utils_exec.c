/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:18:47 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/11 19:21:01 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path(char **env)
{
	char	**tmp;

	tmp = env;
	while (*tmp)
	{
		if (ft_strncmp(*tmp, "PATH=", 5) == 0)
			return (*tmp + 5);
		tmp++;
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

	i = 0;
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

char	*ft_strjoin_gc(char const *s1, char const *s2)
{
	size_t	i;
	char	*p;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s1 && s2)
		return (ft_strdup_env((char *)s2));
	if (s1 && !s2)
		return (ft_strdup_env((char *)s1));
	i = ft_strlen(s1) + ft_strlen(s2);
	p = allocation_env((i + 1) * sizeof(char));
	if (!p)
		return (NULL);
	i = -1;
	j = -1;
	while (s1[++i])
		p[i] = s1[i];
	while (s2[++j])
		p[i++] = s2[j];
	p[i] = '\0';
	return (p);
}

void	set_child_signals(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	clean_all("", 2);
	exit(2);
}
