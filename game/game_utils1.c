/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:03:53 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/24 16:06:51 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"


void clean_exit_game(t_game *game, char *msg)
{
    if (!game)
        exit(1);
    if (msg)
        ft_putstr_fd(msg, 2);
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
    if (game->win)
    {
        mlx_clear_window(game->mlx, game->win);
        mlx_destroy_window(game->mlx, game->win);
    }
    if (game->img)
        mlx_destroy_image(game->mlx, game->img);
    exit(0);
}

void	collect_coin(t_game *game, int new_x, int new_y)
{
	if (game->map.grid[new_y][new_x] == 'C')
	{
		game->map.c_count--;
		game->map.grid[new_y][new_x] = '0';
	}
}

void	update_position(t_game *game, int new_x, int new_y)
{
	static int	moves;

	game->map.player.x = new_x;
	game->map.player.y = new_y;
	moves++;
	ft_putstr_fd("Moves: ", 1);
	ft_putnbr(moves);
	write(1, "\n", 1);
	render_map(game);
}
int	is_valid_move(t_game *game, int new_x, int new_y)
{
	if (new_y < 0 || new_y >= game->map.height
		|| new_x < 0 || new_x >= game->map.width
		|| game->map.grid[new_y][new_x] == '1')
		return (0);
	if (game->map.grid[new_y][new_x] == 'E' && game->map.c_count == 0)
		clean_exit_game(game, "You won!\n");
	else if (game->map.grid[new_y][new_x] == 'E')
		return (0);
	return (1);
}
int	handle_keypress(int keycode, t_game *game)
{
	int	new_x;
	int	new_y;

	new_x = game->map.player.x;
	new_y = game->map.player.y;
	if (keycode == KEY_W || keycode == KEY_UP)
		new_y--;
	else if (keycode == KEY_S || keycode == KEY_DOWN)
		new_y++;
	else if (keycode == KEY_A || keycode == KEY_LEFT)
		new_x--;
	else if (keycode == KEY_D || keycode == KEY_RIGHT)
		new_x++;
	else if (keycode == KEY_ESC)
		clean_exit_game(game, NULL);
	if (!is_valid_move(game, new_x, new_y))
		return (0);
	collect_coin(game, new_x, new_y);
	update_position(game, new_x, new_y);
	return (0);
}
