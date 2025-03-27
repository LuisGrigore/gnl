/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgrigore <lgrigore@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 15:19:28 by lgrigore          #+#    #+#             */
/*   Updated: 2025/03/27 16:07:20 by lgrigore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_null(char **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

char	*join_line(int nl_position, char **buffer)
{
	char	*res;
	char	*tmp;

	if (nl_position <= 0)
	{
		if (**buffer == '\0')
		{
			free_null(buffer);
			return (NULL);
		}
		res = *buffer;
		*buffer = NULL;
		return (res);
	}
	tmp = ft_substr(*buffer, nl_position, BUFFER_SIZE);
	res = *buffer;
	res[nl_position] = '\0';
	*buffer = tmp;
	return (res);
}

char	*read_line(int fd, char **buffer, char *read_return)
{
	ssize_t	bytes_read;
	char	*tmp;
	char	*nl;

	nl = ft_strchr(*buffer, '\n');
	tmp = NULL;
	while (nl == NULL)
	{
		bytes_read = read(fd, read_return, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free_null(buffer);
			return (NULL);
		}
		if (bytes_read == 0)
			return (join_line(0, buffer));
		read_return[bytes_read] = '\0';
		tmp = ft_strjoin(*buffer, read_return);
		free_null(buffer);
		*buffer = tmp;
		nl = ft_strchr(*buffer, '\n');
	}
	return (join_line(nl - *buffer + 1, buffer));
}

char	*get_next_line(int fd)
{
	static char	*buffer = NULL;
	char		*read_return;
	char		*res;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	read_return = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!read_return)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup("");
	res = read_line(fd, &buffer, read_return);
	free_null(&read_return);
	return (res);
}
