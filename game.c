/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    game.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 01:33:07 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/21 00:27:05 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"
#include "mlx.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	clean_exit_game(t_game *game, char *msg)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	clean_map(&game->map);
	exit(0);
}

void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		clean_exit_game(game, "Error: mlx_init() failed.\n");
	game->textures.wall = mlx_xpm_file_to_image(game->mlx,
			"textures/wall.xpm", &(int){64}, &(int){64});
	game->textures.player = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &(int){64}, &(int){64});
	game->textures.collectible = mlx_xpm_file_to_image(game->mlx,
			"textures/coin.xpm", &(int){64}, &(int){64});
	game->textures.exit = mlx_xpm_file_to_image(game->mlx,
			"textures/exit.xpm", &(int){64}, &(int){64});
	game->textures.floor = mlx_xpm_file_to_image(game->mlx,
			"textures/floor.xpm", &(int){64}, &(int){64});
	game->win = mlx_new_window(game->mlx, game->map.width * TILE_SIZE,
			game->map.height * TILE_SIZE, "so_long");

    render_map(game);
     mlx_hook(game->win, 2, 1L<<0, handle_keypress, game);
    mlx_hook(game->win, 17, 0, clean_exit_game, game);
    mlx_loop(game->mlx);
}

void    render_map(t_game *game)
{
    int x;
    int y;

    y = -1;
    while(++y < game->map.height)
    {
        x = -1;
        while(++x < game->map.width)
        {
            mlx_put_image_to_window(game->mlx, game->win, game->textures.floor, x * TILE_SIZE, y * TILE_SIZE);
            if(game->map.grid[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win. game->textures.wall, x * TILE_SIZE, y * TILE_SIZE);
            else if(game->map.grid[y][x] == 'P')
                mlx_put_image_to_window(game->mlx, game->win, game->textures.player, x * TILE_SIZE, y * TILE_SIZE);
            else if(game->map.grid[y][x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->textures.collectible, x * TILE_SIZE, y * TILE_SIZE);
            else if(game->map.grid[y][x] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->textures.exit, x * TILE_SIZE, y * TILE_SIZE);
        }
    }
}