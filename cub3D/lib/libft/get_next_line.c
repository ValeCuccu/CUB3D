/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vacuccu <vacuccu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 19:59:35 by vacuccu           #+#    #+#             */
/*   Updated: 2025/07/31 15:05:47 by vacuccu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#define BUFFER_SIZE 1

static char	*ft_read_and_store(int fd, char **rest, char *buffer)
{
	ssize_t		bt_read;
	char		*tmp;

	while (1)
	{
		bt_read = read(fd, buffer, BUFFER_SIZE);
		if (bt_read == -1)
		{
			free(*rest);
			*rest = NULL;
			return (NULL);
		}
		else if (bt_read == 0)
			break ;
		buffer[bt_read] = '\0';
		if (!*rest)
			*rest = ft_strdup("");
		tmp = *rest;
		*rest = ft_strjoin(tmp, buffer);
		free (tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (*rest);
}

static	char	*ft_extract_excess(char *line)
{
	ssize_t		i;
	char		*excess;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	excess = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!excess)
	{
		free (excess);
		excess = NULL;
		return (NULL);
	}
	line[i + 1] = '\0';
	return (excess);
}

char	*get_next_line(int fd)
{
	static char	*excess;
	char		*buffer;
	static char	*line;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		return (NULL);
	}
	line = ft_read_and_store(fd, &excess, buffer);
	free (buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	excess = ft_extract_excess(line);
	return (line);
}
