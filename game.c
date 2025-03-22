/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 01:33:07 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/22 22:12:45 by oait-si-         ###   ########.fr       */
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
// static int handle_expose(t_game *game) // calls reder_map when the window needs to be redrawn(e.g miinimized/restored)
// {                                       //: Ensures the game screen is refreshed when necessary.
//     render_map((void *)game);
//     return (0);
//}
void	clean_exit_game(t_game *game, char *msg)
{
	if (msg)
		ft_putstr_fd(msg, 2);
    if (game->textures.wall)
        mlx_destroy_image(game->mlx, game->textures.wall);
    if (game->textures.player)
        mlx_destroy_image(game->mlx, game->textures.player);
    if (game->textures.collectible)
        mlx_destroy_image(game->mlx, game->textures.collectible);
    if (game->textures.exit)
        mlx_destroy_image(game->mlx, game->textures.exit);
    if (game->textures.floor)
        mlx_destroy_image(game->mlx, game->textures.floor);
	if (game->win)
    {
            mlx_clear_window(game->mlx, game->win);
		    mlx_destroy_window(game->mlx, game->win);
    }	
    if(game->img)
    {   
        mlx_destroy_image(game->mlx, game->img);
        if(game->mlx)
            free(game->mlx);
        game->mlx = NULL;
    }
    clean_map(&game->map);
	exit(0);
}

static int handle_close(int event, void *param) // calls clean_exit_game whene the X botton is clicked
{                                                      // :ensures the game exit properly 
    t_game *game = (t_game *)param;
    (void)event;
    clean_exit_game(game, NULL);
    return (0);
}
void	init_game(t_game *game) //Initialize mlx -> load texture (mlx_xpm_file_to_image()) -> create game window mlx_new_window() -> sync and render the map
{                                   
	game->mlx = mlx_init(); 
	if (!game->mlx)
		clean_exit_game(game, "Error: mlx_init() failed.\n");
	game->textures.wall = mlx_xpm_file_to_image(game->mlx,
			"textures/wall.xpm", &(int){64}, &(int){64});
    
    if (!game->textures.wall)
            clean_exit_game(game, "Error: Failed to load wall texture.\n");

	game->textures.player = mlx_xpm_file_to_image(game->mlx,
			"textures/player.xpm", &(int){64}, &(int){64});
    
    if (!game->textures.player)
        clean_exit_game(game, "Error: Failed to load player texture.\n");
  
	game->textures.collectible = mlx_xpm_file_to_image(game->mlx,
			"textures/coin.xpm", &game->textures.coin_width, &game->textures.coin_height);
    
    if (!game->textures.collectible)
        clean_exit_game(game, "Error: Failed to load collectible texture.\n");
  
	game->textures.exit = mlx_xpm_file_to_image(game->mlx,
			"textures/exit.xpm", &(int){66}, &(int){66});
    if(!game->textures.exit)
        clean_exit_game(game, "Error: Failed to load exit texture.\n");
    
	game->textures.floor = mlx_xpm_file_to_image(game->mlx,
			"textures/floor.xpm", &(int){64}, &(int){64});
    
    if(!game->textures.floor)
        clean_exit_game(game, "Error: Failed to load floor texture.\n");
    
	game->win = mlx_new_window(game->mlx,game->map.width * TILE_SIZE,game->map.height * TILE_SIZE, "first game");
    if(!game->win)
        clean_exit_game(game, "Error: mlx_new_window() failed.\n");
    
     //mlx_do_sync(game->mlx); // forces MINILIbx to synchronize all pending operations immediately Why is this important?
    // Normally, MLX batches rendering operations and executes them just before the next frame.
    // mlx_do_sync() ensures that everything is drawn right away instead of waiting for MLX's internal refresh cycle
   //  Helps prevent flickering or delays in rendering.
   // Useful if you want to force an immediate redraw before entering the main event loop.



   
    render_map(game); //Calls your render_map() function to draw the game map. // Ensures the initial game screen is properly displayed before the event loop starts.
    //If you don’t call this, the window might appear blank until the first event triggers a redraw.
    
    //mlx_loop_hook(game->mlx, render_map, game); // Calls render_map(game) on every frame refresh. /*Ensures that the game screen updates continuously.
    // Useful for animations or real-time updates.
    // If omitted, the screen only updates when an event occurs (e.g., keypress). 
    
    mlx_hook(game->win, 17, 0, handle_expose , game); // 12 = Expose event on macOS
    mlx_hook(game->win, 2, 1L<<0, handle_keypress, game); // Registers a keypress event (2) → Calls handle_keypress() whenever a key is pressed. // Player presses a key (W, A, S, D, etc.).
    // handle_keypress(keycode, game) gets called.
    // Player moves, and render_map(game) updates the screen.
   // mlx_hook(game->win, 17, 0, handle_close, game); // Registers a window close event (17) → Calls handle_close() when the user clicks the X button.
    //Calls clean_exit_game(game, NULL), which:
      // Frees allocated memory.
     // Destroys the MLX window.
     // Exits properly
    mlx_loop(game->mlx);
    //Enters the MiniLibX event loop, continuously listening for:
   // Key presses
   // Mouse clicks
   // Expose events
    // Window close events
   // Keeps the program running until an exit condition is met.

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
                
            if (game->map.grid[y][x] == 'C')
            {
                //int offest_x = (TILE_SIZE - game->textures.coin_width) / 2;
                //int offest_y = (TILE_SIZE - game->textures.coin_height) / 2;
                mlx_put_image_to_window(game->mlx, game->win, game->textures.collectible, x * TILE_SIZE   , y * TILE_SIZE  );
            }
            if (game->map.grid[y][x] == 'P')
                mlx_put_image_to_window(game->mlx, game->win, game->textures.player, x * TILE_SIZE, y * TILE_SIZE);
            if (game->map.grid[y][x] == 'E')
                mlx_put_image_to_window(game->mlx, game->win, game->textures.exit, x * TILE_SIZE, y * TILE_SIZE);
        }
    }
   mlx_put_image_to_window(game->mlx, game->win, game->textures.player, 
        game->map.player.x * TILE_SIZE, game->map.player.y * TILE_SIZE);
    return (0);
}

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
    static int moves = 0;
    int new_x = game->map.player.x;
    int new_y = game->map.player.y;
    //int old_x = game->map.player.x; // Save current position
   // int old_y = game->map.player.y;
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
        new_x < 0 || new_x >= game->map.width || 
        game->map.grid[new_y][new_x] == '1')
            return (0);
    if(game->map.grid[new_y][new_x] == 'E' && game->map.c_count == 0)
            clean_exit_game(game, "You won!\n");
    else if(game->map.grid[new_y][new_x] == 'E')
            return (0); // Exit is blocked until coins are collected
    
    if (game->map.grid[new_y][new_x] == 'C')
    {
        game->map.c_count--; // Decrement coin count
        game->map.grid[new_y][new_x] = '0'; // Remove coin from grid
    }
      // Update grid and player position
    // game->map.grid[old_y][old_x] = '0'; // Clear old position
    // game->map.grid[new_y][new_x] = 'P'; // Set new position
    game->map.player.x = new_x;
    game->map.player.y = new_y;
       
    moves++;
    ft_putstr_fd("Moves: ", 1);
    ft_putnbr(moves);
    write(1, "\n", 1);
    render_map(game);
    return 0;
}