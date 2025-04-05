/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_flood_fill.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 02:05:54 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/28 11:50:28 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	flood_fill(t_map *map, char **grid, int x, int y)
{
	if (y >= map->height || x >= map->width || grid[y][x] == '1')
		return ;
	if (grid[y][x] == 'E')
		map->exit_reachable++;
	if (grid[y][x] == 'C')
		map->c_collected++;
	grid[y][x] = '1';
	flood_fill(map, grid, x + 1, y);
	flood_fill(map, grid, x - 1, y);
	flood_fill(map, grid, x, y + 1);
	flood_fill(map, grid, x, y - 1);
}

void	flood_fill_1(t_map *map, char **grid, int x, int y)
{
	if (y >= map->height || x >= map->width || grid[y][x] == '1'
		|| grid[y][x] == 'E')
		return ;
	if (grid[y][x] == 'C')
		map->c_collected++;
	grid[y][x] = '1';
	flood_fill_1(map, grid, x + 1, y);
	flood_fill_1(map, grid, x - 1, y);
	flood_fill_1(map, grid, x, y + 1);
	flood_fill_1(map, grid, x, y - 1);
}

int	check_path_to_c(t_map *map)
{
	char	**test;

	test = mimc_map(map);
	if (!test)
		return (0);
	map->exit_reachable = 0;
	map->c_collected = 0;
	flood_fill_1(map, test, map->player.x, map->player.y);
	free_dubel(test, map->height);
	return (map->c_collected == map->c_count);
}

int	validate_components(t_map *map)
{
	char	**new;

	if (!check_path_to_c(map))
		return (0);
	new = mimc_map(map);
	if (!new)
		return (0);
	map->exit_reachable = 0;
	map->c_collected = 0;
	flood_fill(map, new, map->player.x, map->player.y);
	free_dubel(new, map->height);
	return (map->c_collected == map->c_count && map->exit_reachable == 1
		&& map->c_collected > 0);
}
