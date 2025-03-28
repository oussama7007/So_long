/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 02:12:56 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/25 11:51:31 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_textures(t_game *game)
{
	if (game->s_textures.wall)
		mlx_destroy_image(game->mlx, game->s_textures.wall);
	if (game->s_textures.player)
		mlx_destroy_image(game->mlx, game->s_textures.player);
	if (game->s_textures.collectible)
		mlx_destroy_image(game->mlx, game->s_textures.collectible);
	if (game->s_textures.exit)
		mlx_destroy_image(game->mlx, game->s_textures.exit);
	if (game->s_textures.floor)
		mlx_destroy_image(game->mlx, game->s_textures.floor);
}

int	handle_close(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	clean_exit_game(game, NULL);
	return (0);
}

void	clean_exit_game(t_game *game, char *msg)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	if (!game)
		exit(1);
	free_textures(game);
	if (game->win)
	{
		mlx_clear_window(game->mlx, game->win);
		mlx_destroy_window(game->mlx, game->win);
	}
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	exit(0);
}

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
