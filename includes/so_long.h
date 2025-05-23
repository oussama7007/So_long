/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Your Name <your.email@example.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 13:00:00 by Your Name        #+#    #+#             */
/*   Updated: 2025/03/24 13:00:00 by Your Name        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <fcntl.h>
# include "mlx.h"
# include <stdlib.h>
# include "get_next_line.h"

# define TILE_SIZE 60
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_map
{
	char		**grid;
	int			height;
	int			width;
	t_point		player;
	t_point		exit;
	int			p_count;
	int			e_count;
	int			c_count;
	int			exit_reachable;
	int			c_collected;
}	t_map;

typedef struct s_game
{
	void		*mlx;
	t_map		map;
	void		*win;
	struct
	{
		void	*wall;
		void	*player;
		void	*exit;
		void	*collectible;
		void	*floor;
		int		coin_width;
		int		coin_height;
	}	s_textures;
	int			moves;
	int			game_over;
	void		*img;
}	t_game;

/* Parsing */
int		validate_map(char *filename, t_map *map);
int		get_map_dimensions(int fd, t_map *map);
int		load_map(int fd, t_map *map);
int		is_map_closed(t_map *map);
int		check_extension(char *filename);
int		init_map_storage(t_map *map);
int		process_line(t_map *map, char *line, int y);
int		check_path_to_c(t_map *map);
char	**mimc_map(t_map *map);
int		validate_components(t_map *map);

/* Game */
void	init_game(t_game *game);
int		handle_keypress(int keycode, t_game *game);
void	clean_exit_game(t_game *game, char *msg);
int		render_map(void *game_ptr);
void	update_position(t_game *game, int new_x, int new_y);
void	collect_coin(t_game *game, int new_x, int new_y);
int		is_valid_move(t_game *game, int new_x, int new_y);
void	init_window(t_game *game);
void	load_textures(t_game *game);
int		handle_close(void *param);
void	free_textures(t_game *game);
void	render_cell(t_game *game, int x, int y);
void	put_image(t_game *game, void *img, int x, int y);
int		is_valid_key_press(int keycode);

/* Process line */
int		handle_invalid_char(char *line, int y);
int		handle_player_and_exit(t_map *map, int x, int y);
int		handle_coin_and_invalid_count(t_map *map, int x, int y);
int		process_line(t_map *map, char *line, int y);

/* Utils_parsing */
void	free_dubel(char **str, int height);
char	*ft_strdup(char *str);
void	clean_map(t_map *map);
void	clean_exit(t_map *map, int fd, char *str);
void	flood_fill(t_map *map, char **grid, int x, int y);
void	flood_fill_1(t_map *map, char **grid, int x, int y);
void	*ft_memset(void *str, int value, size_t len);

#endif
