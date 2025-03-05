#ifndef SO_LONG_H
# define SO_LONG_H

#include <fcntl.h>
#include "mlx.h"
#include <stdlib.h>
#include "get_next_line.h"

int   check_extention(char *str);
int   main(int ac , char **av);
int validate_map(char *str);
int extract_map_content(int fd);
int count_num_of_line(int fd);

#endif 