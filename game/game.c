/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:01:45 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/24 16:07:01 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void	load_textures(t_game *game)
{
	game->s_textures.wall = mlx_xpm_file_to_image(game->mlx,
			"textures/wall.xpm", &(int){64}, &(int){64});
	if (!game->s_textures.wall)
		clean_exit_game(game, "Error: Failed to load wall texture.\n");
	game->s_textures.player = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &(int){64}, &(int){64});
	if (!game->s_textures.player)
		clean_exit_game(game, "Error: Failed to load player texture.\n");
	game->s_textures.collectible = mlx_xpm_file_to_image(game->mlx,
			"textures/coin.xpm", &game->s_textures.coin_width,
			&game->s_textures.coin_height);
	if (!game->s_textures.collectible)
		clean_exit_game(game, "Error: Failed to load collectible texture.\n");
	game->s_textures.exit = mlx_xpm_file_to_image(game->mlx,
			"textures/exit.xpm", &(int){64}, &(int){64});
	if (!game->s_textures.exit)
		clean_exit_game(game, "Error: Failed to load exit texture.\n");
	game->s_textures.floor = mlx_xpm_file_to_image(game->mlx,
			"textures/floor.xpm", &(int){64}, &(int){64});
	if (!game->s_textures.floor)
		clean_exit_game(game, "Error: Failed to load floor texture.\n");
}

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

int render_map(void *game_ptr)
{
    t_game *game;
    int x;
    int y;

    game = (t_game *)game_ptr;
    y = -1;
    while (++y < game->map.height)
    {
        x = -1;
        while (++x < game->map.width)
        {
            mlx_put_image_to_window(game->mlx, game->win,
                game->s_textures.floor, x * TILE_SIZE, y * TILE_SIZE);
            if (game->map.grid[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win,
                    game->s_textures.wall, x * TILE_SIZE, y * TILE_SIZE);
            if (game->map.grid[y][x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win,
                    game->s_textures.collectible, x * TILE_SIZE, y * TILE_SIZE);
            if (game->map.grid[y][x] == 'P')
                mlx_put_image_to_window(game->mlx, game->win,
                    game->s_textures.player, x * TILE_SIZE, y * TILE_SIZE);
            if (game->map.grid[y][x] == 'E')
                mlx_put_image_to_window(game->mlx, game->win,
                    game->s_textures.exit, x * TILE_SIZE, y * TILE_SIZE);
        }
    }
    mlx_put_image_to_window(game->mlx, game->win,
        game->s_textures.player, game->map.player.x * TILE_SIZE,
        game->map.player.y * TILE_SIZE);
    return (0);
}

int handle_close(void *param)
{
    t_game *game;

    game = (t_game *)param;
    clean_exit_game(game, NULL);
    return (0);
}





