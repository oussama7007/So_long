/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 02:08:01 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/24 11:37:34 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_extention(char *filename)
{
	int		i;
	int		j;
	char	*s;

	j = 0;
	s = "reb.";
	i = 0;
	while (filename[i])
		i++;
	if (i < 4)
		return (0);
	while (j <= 3)
	{
		if (filename[--i] != s[j])
			return (0);
		j++;
	}
	return (1);
}

int	get_map_dimensions(int fd, t_map *map)
{
	char	*line;
	int		first_line_len;
	size_t	len;

	first_line_len = -1;
	map->height = 0;
	line = get_next_line(fd);
	while (line)
	{
		len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[--len] = '\0';
		if (first_line_len == -1)
			first_line_len = len;
		else if ((int)len != first_line_len)
			return (free(line), 0);
		free(line);
		map->height++;
		line = get_next_line(fd);
	}
	map->width = first_line_len;
	return (map->height > 2 && map->width > 2 && map->height <= 24
		&& map->width <= 43);
}

int	init_map_storage(t_map *map)
{
	if (map->height < 3 || map->width < 3)
		return (0);
	map->grid = (char **)malloc(sizeof(char *) * map->height);
	if (!map->grid)
		return (0);
	ft_memset(map->grid, 0, sizeof(char *) * map->height);
	return (1);
}

int	is_map_closed(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->height)
	{
		if (map->grid[y][0] != '1' || map->grid[y][map->width - 1] != '1')
			return (0);
	}
	x = -1;
	while (++x < map->width)
	{
		if (map->grid[0][x] != '1' || map->grid[map->height - 1][x] != '1')
			return (0);
	}
	return (1);
}
