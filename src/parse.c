/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:00:51 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/24 13:14:37 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	load_map(int fd, t_map *map)
{
	char	*line;
	int		y;

	if (fd < 0 || !init_map_storage(map))
		return (0);
	y = -1;
	while (++y < map->height)
	{
		line = get_next_line(fd);
		if (!line || !process_line(map, line, y))
		{
			if (line)
				free(line);
			return (clean_map(map), 0);
		}
		free(line);
	}
	return (1);
}

char	**mimc_map(t_map *map)
{
	char	**copy;
	int		y;

	copy = (char **)malloc(sizeof(char *) * map->height);
	if (!copy)
		return (NULL);
	y = -1;
	while (++y < map->height)
	{
		copy[y] = ft_strdup(map->grid[y]);
		if (!copy[y])
		{
			free_dubel(copy, y);
			return (NULL);
		}
	}
	return (copy);
}

int	validate_map(char *filename, t_map *map)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (!check_extension(filename) || fd < 0)
		return (clean_exit(map, fd,
				"Error\nfile's extension/file's name is incorrect\n"), 0);
	if (!get_map_dimensions(fd, map))
		return (clean_exit(map, fd,
				"Error\nincorrect dimensions: 3x3 <-> 24x44\n"), 0);
	close(fd);
	fd = open(filename, O_RDONLY);
	if (fd < 0 || !load_map(fd, map))
		return (clean_exit(map, fd, "Error\nInvalid element\n"), 0);
	close(fd);
	if (!is_map_closed(map))
		return (clean_exit(map, -1, "Error\nMap isn't closed with walls\n"), 0);
	if (!validate_components(map))
		return (clean_exit(map, -1,
				"Error\nExit isn't reachable or coins aren't collected\n"), 0);
	return (1);
}
