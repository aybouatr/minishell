/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:19:25 by aybouatr          #+#    #+#             */
/*   Updated: 2025/05/08 19:12:35 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*allocation_env(size_t nbr_byt)
{
	void	*ptr;

	ptr = malloc(nbr_byt);
	if (!ptr)
	{
		clean_memory("the malloc fails to allocate for the env\n", 1);
		clean_env();
		exit(EXIT_FAILURE);
	}
	clean_env_or_save(ptr, save);
	return (ptr);
}

char	*ft_strdup_env(char *s)
{
	size_t	i;
	char	*p;

	i = ft_strlen(s);
	p = (char *)allocation_env((i + 1) * sizeof(char));
	if (!p)
	{
		clean_memory("the malloc fails to allocate for the env\n", 1);
		clean_env();
		exit(EXIT_FAILURE);
	}
	i = -1;
	while (s[++i])
		p[i] = s[i];
	p[i] = '\0';
	return (p);
}

void	start_env(void)
{
	int	count;

	g_data.cwd = getcwd(NULL, 0);
	count = tab_counter(__environ);
	g_data.env = allocation_env_2d((count + 1));
	count = -1;
	while (__environ[++count])
	{
		g_data.env[count] = ft_strdup_env(__environ[count]);
	}
	g_data.sig_here_doc = 0;
	g_data.env[count] = NULL;
	g_data.or_stdin = dup(0);
	g_data.or_stdout = dup(1);
	g_data.exit_status = 0;
}

int	tab_counter(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**allocation_env_2d(size_t nbr_ptr)
{
	char	**ptr;

	ptr = malloc(nbr_ptr * sizeof(char *));
	if (!ptr)
	{
		clean_memory("the malloc fails to allocate for the env\n", 1);
		clean_env();
		exit(EXIT_FAILURE);
	}
	clean_env_or_save_2d(ptr, save);
	return (ptr);
}
