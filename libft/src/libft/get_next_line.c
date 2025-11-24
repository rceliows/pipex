/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rceliows <rceliows@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 15:47:06 by rceliows          #+#    #+#             */
/*   Updated: 2025/04/30 15:47:27 by rceliows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

static char	*read_chunk(int fd, char *buffer, char *read_buffer)
{
	ssize_t	bytes_read;
	char	*temp;

	bytes_read = read(fd, read_buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(buffer);
		return (NULL);
	}
	read_buffer[bytes_read] = '\0';
	if (!buffer)
	{
		buffer = ft_strdup("");
		if (!buffer)
			return (NULL);
	}
	temp = ft_strjoin(buffer, read_buffer);
	free(buffer);
	return (temp);
}

static char	*read_file(int fd, char *buffer)
{
	char	*read_buffer;
	char	*result;

	read_buffer = malloc(BUFFER_SIZE + 1);
	if (!read_buffer)
		return (NULL);
	result = buffer;
	if (!result || !ft_strchr(result, '\n'))
	{
		while (1)
		{
			result = read_chunk(fd, result, read_buffer);
			if (!result)
			{
				free(read_buffer);
				return (NULL);
			}
			if (ft_strchr(result, '\n') || read_buffer[0] == '\0')
				break ;
		}
	}
	free(read_buffer);
	return (result);
}

static char	*extract_line(char *buffer, size_t i)
{
	char	*line;

	if (!buffer || !buffer[0])
		return (NULL);
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	ft_memcpy(line, buffer, i);
	line[i] = '\0';
	return (line);
}

static char	*update_buffer(char *buffer, size_t i)
{
	char	*new_buffer;

	if (!buffer)
		return (NULL);
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = ft_strdup(buffer + i);
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	size_t		i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = extract_line(buffer, i);
	buffer = update_buffer(buffer, i);
	return (line);
}
