#ifndef SO_LONG_H
# define SO_LONG_H

#include <fcntl.h>
#include "mlx.h"
#include <stdlib.h>
#include "get_next_line.h"

typedef struct s_point{
    int x;
    int y;
}   t_point;

typedef struct s_map{
    char **grid;
    int height;
    int width;
    t_point player;
    t_point exit;
    int     p_count;
    int     e_count;
    int     c_count;
    int     reachable;      
}   t_map;

int   check_extention(char *str);
int   main(int ac , char **av);
int validate_map(char *str);
int extract_map_content(int fd);
int count_num_of_line(int fd);

#endif 