/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 12:17:40 by oait-si-          #+#    #+#             */
/*   Updated: 2024/12/17 11:39:25 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*next_line(char *buffer)
{
	int		i;
	char	*new_line;
	int		j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free(buffer), buffer = NULL, NULL);
	new_line = malloc(ft_strlen(buffer) - i + 1);
	if (!new_line)
		return (free(buffer), buffer = NULL, NULL);
	i++;
	while (buffer[i])
		new_line[j++] = buffer[i++];
	new_line[j] = '\0';
	free(buffer);
	return (new_line);
}

char	*new_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer || !buffer[0])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*read_file(int fd, char *static_buffer)
{
	char	*buffer;
	int		bytes;
	char	*temp;

	bytes = 1;
	buffer = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buffer), free(static_buffer), NULL);
		buffer[bytes] = '\0';
		temp = static_buffer;
		static_buffer = ft_strjoin(static_buffer, buffer);
		if (!static_buffer)
			return (free(buffer), free(temp), NULL);
		if (temp)
			free(temp);
		if (ft_strchr(static_buffer, '\n'))
			break ;
	}
	free(buffer);
	return (static_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (!buffer)
		return (free(buffer), buffer = NULL, NULL);
	line = new_line(buffer);
	if (!line)
		return (free(buffer), buffer = NULL, NULL);
	buffer = next_line(buffer);
	return (line);
}
