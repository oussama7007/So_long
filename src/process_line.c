/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 11:12:09 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/24 11:12:27 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	handle_invalid_char(char *line, int y, t_map *map)
{
	if (!ft_strchr("01PEC", line[y]))
	{
		free(map->grid[y]);
		map->grid[y] = NULL;
		return (0);
	}
	return (1);
}

int	handle_player_and_exit(t_map *map, int x, int y)
{
	if (map->grid[y][x] == 'P' && ++map->p_count)
	{
		map->player = (t_point){x, y};
		map->grid[y][x] = '0';
	}
	else if (map->grid[y][x] == 'E' && ++map->e_count)
		map->exit = (t_point){x, y};
	return (1);
}

int	handle_coin_and_invalid_count(t_map *map, int x, int y)
{
	if (map->grid[y][x] == 'C')
		map->c_count++;
	if (map->p_count > 1 || map->e_count > 1)
	{
		free(map->grid[y]);
		map->grid[y] = NULL;
		return (0);
	}
	return (1);
}

int	process_line(t_map *map, char *line, int y)
{
	size_t	len;
	int		x;

	if (!line || !(map->grid[y] = ft_strdup(line)))
		return (0);
	len = ft_strlen(map->grid[y]);
	if (len > 0 && map->grid[y][len - 1] == '\n' && len--)
		map->grid[y][len] = '\0';
	if (len != (size_t)map->width)
		return (free(map->grid[y]), map->grid[y] = NULL, 0);
	x = -1;
	while (++x < map->width)
	{
		if (!handle_invalid_char(map->grid[y], x, map))
			return (0);
		if (!handle_player_and_exit(map, x, y))
			return (0);
		if (!handle_coin_and_invalid_count(map, x, y))
			return (0);
	}
	return (1);
}
