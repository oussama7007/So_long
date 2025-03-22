#ifndef SO_LONG_H
# define SO_LONG_H

#include <fcntl.h>
#include "mlx.h"
#include <stdlib.h>
#include "get_next_line.h"



# define TILE_SIZE 64
# define KEY_ESC 53
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124

typedef struct s_point{
    int x;
    int y;
} t_point;
typedef struct s_map{
    char **grid;
    int height;
    int width;
    t_point player;
    t_point exit;
    int     p_count;
    int     e_count;
    int     c_count;
    int     exit_reachable;
    int     c_collected;     
}   t_map;

typedef struct s_game{
    void *mlx;
    t_map map;
    void *win;
    
    struct {
        void *wall;
        void *player;
        void *exit;
        void *collectible;
        void *floor;
    } textures;

    int moves;
    int game_over;
    void *img;
} t_game;

// Parsing
int validate_map(char *filename, t_map *map);
int get_map_dimensions(int fd, t_map *map);
int load_map(int fd, t_map *map);
int is_map_closed(t_map *map);

// Game
void init_game(t_game *game);
int   handle_keypress(int keycode, t_game *game);


int    render_map(void *game);
//void clean_exit(t_game *game, char *msg);

// Utils
void clean_map(t_map *map);
int check_extention(char *filename);
void clean_exit_game(t_game *game, char *msg);
void clean_exit(t_map *map, int fd, char *str);

void ft_putstr_fd(char *s, int fd);
void  *ft_memset(void *str, int value, size_t len);
void    ft_putnbr(int nb);
#endif 
   