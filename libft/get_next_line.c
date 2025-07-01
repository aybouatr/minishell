/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oachbani <oachbani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 15:26:12 by oachbani          #+#    #+#             */
/*   Updated: 2025/05/11 19:31:58 by oachbani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_read_add(char *str, int fd)
{
	int		readed;
	char	*buffer;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (free(str), NULL);
	readed = 1;
	while (!ft_strchrget(str, '\n') && readed)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed == -1)
			return (free(buffer), free(str), NULL);
		buffer[readed] = '\0';
		str = ft_strjoinget(str, buffer);
		if (!str)
			return (free(str), NULL);
	}
	free(buffer);
	return (str);
}

char	*ft_extract(char *str)
{
	size_t	len;
	char	*buffer;

	if (!str || !(*str))
		return (NULL);
	len = 0;
	while (str[len] && str[len] != '\n')
		len++;
	buffer = (char *)malloc(len + 2);
	if (!buffer)
		return (free(str), NULL);
	len = 0;
	while (str[len] && str[len] != '\n')
	{
		buffer[len] = str[len];
		len++;
	}
	if (str[len] == '\n')
	{
		buffer[len] = str[len];
		len++;
	}
	buffer[len] = '\0';
	return (buffer);
}

char	*ft_remaining(char *str)
{
	size_t	clear;
	char	*buffer;
	size_t	save;

	clear = 0;
	save = 0;
	while (str[clear] && str[clear] != '\n')
		clear++;
	if (!str[clear])
		return (free(str), NULL);
	buffer = malloc(ft_strlenget(str) - clear + 1);
	if (!buffer)
		return (free(str), NULL);
	clear++;
	while (str[clear])
		buffer[save++] = str[clear++];
	buffer[save] = '\0';
	free(str);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*save;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = ft_read_add(line, fd);
	if (!line)
		return (NULL);
	save = ft_extract(line);
	if (!save)
	{
		free(line);
		line = NULL;
		return (NULL);
	}
	free(line);
	line = NULL;
	return (save);
}
