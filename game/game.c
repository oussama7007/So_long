/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:01:45 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/24 16:27:30 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx, game->map.width * TILE_SIZE,
			game->map.height * TILE_SIZE, "first game");
	if (!game->win)
		clean_exit_game(game, "Error: mlx_new_window() failed.\n");
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		clean_exit_game(game, "Error: mlx_init() failed.\n");
	load_textures(game);
	init_window(game);
	render_map(game);
	mlx_hook(game->win, 17, 0, handle_close, game);
	mlx_hook(game->win, 2, 1L << 0, handle_keypress, game);
	mlx_loop(game->mlx);
}

void	put_image(t_game *game, void *img, int x, int y)
{
	mlx_put_image_to_window(game->mlx, game->win,
		img, x * TILE_SIZE, y * TILE_SIZE);
}

void	render_cell(t_game *game, int x, int y)
{
	put_image(game, game->s_textures.floor, x, y);
	if (game->map.grid[y][x] == '1')
		put_image(game, game->s_textures.wall, x, y);
	if (game->map.grid[y][x] == 'C')
		put_image(game, game->s_textures.collectible, x, y);
	if (game->map.grid[y][x] == 'P')
		put_image(game, game->s_textures.player, x, y);
	if (game->map.grid[y][x] == 'E')
		put_image(game, game->s_textures.exit, x, y);
}

int	render_map(void *game_ptr)
{
	t_game	*game;
	int		x;
	int		y;

	game = (t_game *)game_ptr;
	y = -1;
	while (++y < game->map.height)
	{
		x = -1;
		while (++x < game->map.width)
			render_cell(game, x, y);
	}
	put_image(game, game->s_textures.player,
		game->map.player.x, game->map.player.y);
	return (0);
}
