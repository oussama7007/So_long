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
static int handle_expose(t_game *game)
{
    render_map((void *)game);
    return (0);
}
void	clean_exit_game(t_game *game, char *msg)
{
	if (msg)
		ft_putstr_fd(msg, 2);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);	
    if(game->img)
        mlx_destroy_image(game->mlx, game->img);
    clean_map(&game->map);
	exit(0);
}

static int handle_close(int event, void *param)
{
    t_game *game = (t_game *)param;
    (void)event;
    clean_exit_game(game, NULL);
    return (0);
}
void	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		clean_exit_game(game, "Error: mlx_init() failed.\n");
	game->textures.wall = mlx_xpm_file_to_image(game->mlx,
			"textures/wall.xpm", &(int){64}, &(int){64});
    
    if (!game->textures.wall)
            clean_exit_game(game, "Error: Failed to load wall texture.\n");
    ft_putstr_fd("Wall texture loaded.\n", 1);
	game->textures.player = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &(int){64}, &(int){64});
    
    if (!game->textures.player)
        clean_exit_game(game, "Error: Failed to load player texture.\n");
    ft_putstr_fd("player texture loaded.\n", 1);
	game->textures.collectible = mlx_xpm_file_to_image(game->mlx,
			"textures/coin.xpm", &(int){64}, &(int){64});
    
    if (!game->textures.collectible)
        clean_exit_game(game, "Error: Failed to load collectible texture.\n");
    ft_putstr_fd("collectible texture loaded.\n", 1);
	game->textures.exit = mlx_xpm_file_to_image(game->mlx,
			"textures/exit.xpm", &(int){64}, &(int){64});
    if(!game->textures.exit)
        clean_exit_game(game, "Error: Failed to load exit texture.\n");
    ft_putstr_fd("exit texture loaded.\n", 1);
	game->textures.floor = mlx_xpm_file_to_image(game->mlx,
			"textures/floor.xpm", &(int){64}, &(int){64});
    
    if(!game->textures.floor)
        clean_exit_game(game, "Error: Failed to load floor texture.\n");
    ft_putstr_fd("floor texture loaded.\n", 1);
	game->win = mlx_new_window(game->mlx, game->map.width * TILE_SIZE,
			game->map.height * TILE_SIZE, "so_long");
    if(!game->win)
        clean_exit_game(game, "Error: mlx_new_window() failed.\n");
    ft_putstr_fd("mlx_new_window() success.\n", 1);
    //render_map(game);
    
    mlx_loop_hook(game->mlx, render_map, game);
    
    mlx_hook(game->win, 12, 0, handle_expose, game); // 12 = Expose event on macOS
    mlx_hook(game->win, 2, 1L<<0, handle_keypress, game);
    mlx_hook(game->win, 17, 0, handle_close, game);
    mlx_loop(game->mlx);

}
int render_map(void *game_ptr)
{

    t_game  *game = (t_game *)game_ptr; // Add this line
    int x;
    int y;

    y = -1;
    while (++y < game->map.height)
    {
        x = -1;
        while (++x < game->map.width)
        {
            mlx_put_image_to_window(game->mlx, game->win, game->textures.floor, x * TILE_SIZE, y * TILE_SIZE);
            if (game->map.grid[y][x] == '1')
                mlx_put_image_to_window(game->mlx, game->win, game->textures.wall, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map.grid[y][x] == 'P')
                mlx_put_image_to_window(game->mlx, game->win, game->textures.player, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map.grid[y][x] == 'C')
                mlx_put_image_to_window(game->mlx, game->win, game->textures.collectible, x * TILE_SIZE, y * TILE_SIZE);
            else if (game->map.grid[y][x] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->textures.exit, x * TILE_SIZE, y * TILE_SIZE);
        }
    }
    ft_putstr_fd("Map rendered.\n", 1);
    return (0);
}
// void    render_map(void *game)
// {
//     t_game *game = (t_game *)game_ptr;
//     int x;
//     int y;

//     y = -1;
//     while(++y < game->map.height)
//     {
//         x = -1;
//         while(++x < game->map.width)
//         {
//             mlx_put_image_to_window(game->mlx, game->win, game->textures.floor, x * TILE_SIZE, y * TILE_SIZE);
//             if(game->map.grid[y][x] == '1')
//                  mlx_put_image_to_window(game->mlx, game->win, game->textures.wall, x * TILE_SIZE, y * TILE_SIZE);
//             else if(game->map.grid[y][x] == 'P')
//                 mlx_put_image_to_window(game->mlx, game->win, game->textures.player, x * TILE_SIZE, y * TILE_SIZE);
//             else if(game->map.grid[y][x] == 'C')
//                 mlx_put_image_to_window(game->mlx, game->win, game->textures.collectible, x * TILE_SIZE, y * TILE_SIZE);
//             else if(game->map.grid[y][x] == 'E')
//                 mlx_put_image_to_window(game->mlx, game->win, game->textures.exit, x * TILE_SIZE, y * TILE_SIZE);
//         }
//     }
//     ft_putstr_fd("Map rendered.\n", 1);
//    // mlx_do_sync(game->mlx);
//}

void    ft_putnbr(int nb)
{
    int a;

    if(nb > 10)
        ft_putnbr(nb / 10);
    a = nb % 10 + '0';
    write(1, &a, 1);
}


int        handle_keypress(int keycode, t_game *game)
{
    static int moves;

    moves = 0;
    int new_x = game->map.player.x;
    int new_y = game->map.player.y;

    if(keycode == KEY_W || keycode == KEY_UP)
        new_y--;
    else if(keycode == KEY_S || keycode == KEY_DOWN)
        new_y++;
    else if(keycode == KEY_A || keycode == KEY_LEFT)
         new_x--;
    else if(keycode == KEY_D || keycode == KEY_RIGHT)
        new_x++;
    else if (keycode == KEY_ESC)
        clean_exit_game(game, NULL);
    
    if (new_y < 0 || new_y >= game->map.height || 
        new_x < 0 || new_x >= game->map.width)
            return (0);
    if(game->map.grid[new_y][new_x] != '1')
    {
        moves++;
        ft_putstr_fd("Moves: ", 1);
        ft_putnbr(moves);

        game->map.player.x = new_x;
        game->map.player.y = new_y;
        //render_map(game);
    }
    return 0;
}