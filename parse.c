/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:00:51 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/10 20:34:22 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int   check_extention(char *filename)
{
    int j = 0;
    int i;
    i = 0;
    
    char *s = "reb.";
    while(filename[i])
        i++;
    if(i < 4)
        return 0;
    while(j <= 3)
    {
          if(filename[--i] != s[j])
               return 0;
           j++;
    }
    return 1;
}

void clean_map(t_map *map)
{
    int i;

    i = -1;
    if(map->grid)
    {
        while(++i < map->height)
            free(map->grid[i]);
        free(map->grid);
    }
}
void    ft_putstr(char *str)
{
    while(*str)
    {
        write(1, &str, 1);
        str++
    }
}
int clean_exit(t_map *map, int status, int fd, char *str)
{
    if(map) 
        clean_map(map);
    if(str) 
        ft_putstr(str);
    if(fd > 0) 
        close(fd);
    return (status);
}
int get_map_dimensions(int fd, t_map *map)
{
    char *line;
    int first_line_len;
    size_t len;

    first_line_len = -1;
    map->height = 0;
    while((line = get_next_line(fd)))
    {
        len = ft_strlen(line);
        if(len > 0 && line[len -1] == '\n')
            line[--len] = '\0';
        if(first_line_len == -1)
            first_line_len = len;
        else if((int)len != first_line_len)
        {
            free(line);
            return (0);
        }
        free(line);
        map->height++;
    }
    map->width = first_line_len;
   return (map->height > 2 && map->width > 2); // return (map->height > 2 && map->width > 4);
}
int init_map_storage(t_map *map)
{
       
	if (map->height < 3 || map->width < 3)
		return (0);
	map->grid = (char **)malloc(sizeof(char *) * map->height);
	if (!map->grid)
		return (0);
	ft_memset(map->grid, 0, sizeof(char *) * map->height);
	return (1); 
}

int	process_line(t_map *map, char *line, int y)
{
	size_t	len;
	int		x;

	if (!line || !(map->grid[y] = ft_strdup(line)))
		return (free(line),0);
	len = ft_strlen(map->grid[y]);
	if (len > 0 && map->grid[y][len - 1] == '\n' && len--)
		map->grid[y][len] = '\0';
	if (len != (size_t)map->width)
		return (free(map->grid[y]), 0);
	x = -1;
	while (++x < map->width)
	{
		if (map->grid[y][x] == 'P' && ++map->p_count)
			map->player = (t_point){x, y};
		else if (map->grid[y][x] == 'E' && ++map->e_count)
			map->exit = (t_point){x, y};
		else if (map->grid[y][x] == 'C')
			map->c_count++;
		else if (!ft_strchr("01", map->grid[y][x]))
			return (free(map->grid[y]), 0);
		if (map->p_count > 1 || map->e_count > 1)
			return (free(map->grid[y]), 0);
	}
	return (1);
}
int     load_map(int fd, t_map *map)
{
    char *line;
    int y;

    if(fd < 0 || !init_map_storage(map))
        return 0;
    y = -1;
    while( ++y < map->height)
    {
        line = get_next_line(fd);
        if(!line || !process_line(map, line, y))
        {
            if (line)
                 free(line);
            return(clean_map(map),0);
        }
        free(line);
    }
    // ******** test this part  by rmoving it and add white space the map in separate line leak ...  /\/
    line = get_next_line(fd);
    if(line)
    {
        free(line);
        return(clean_map(map),0);
    }
    return (1);
}
int     is_map_closed(t_map *map)
{
        int y;
        int x;

        y = -1;
        x = -1;
        while(++y < map->height)
        {
            if(map->grid[y][0] != '1' || map->grid[y][map->width - 1] != '1')
                return 0;
        }
        while(++x < map->width)
        {
            if(map->grid[0][x] != '1' || map->grid[map->height - 1] != '1')
                return 0;
        }
        return 1;
}


/*//How It Works
Duplicate the Map:

Creates a copy of the map to avoid modifying the original.

Initialize Visited Matrix:

Tracks which cells have been explored.

Start BFS from Player’s Position:

Adds the player’s starting position to the queue.

Explore Neighbors:

Checks up, down, left, and right for valid, unvisited cells.

Adds valid cells to the queue.

Track Collectibles and Exit:

Counts Cs and checks if E is reachable.

Cleanup:

Frees the duplicated grid and visited matrix.

Validation:

Returns 1 if all Cs are collected and E is reachable; otherwise, 0.*/
char *ft_strdup(char *str)
{
    char *new;
    int i;
    int size;

    size = ft_strlen(str);
    i = -1;
    new = malloc(size + 1);
    if(!new)
        return NULL;
    while(++i < size)
        new[i] = str[i];
    new[i] = '\0';
    return new;
}
char **mimc_map(t_map *map)
{
        char **copy;
        int y;
        
        copy = (char **)malloc((sizeof(char *) * map->height));
        it(!copy)
            return NULL:
        y = -1;
        while(++y < map->height)
        {
            copy[y] = ft_strdup(map->grid[y]);
            if(!copy[y])
            {
                while(y-- >= 0)
                    free(copy[y])
                free(copy);
                return NULL;
            }
        }
        return (copy);
}

int validate_components(t_map *map)
{
    char **new;

    new = mimc_map(map);   
}
int validate_map(char *filename)
{
    int fd;
    t_map map;

    ft_memset(&map, 0, sizeof(t_map));
    fd = open(filename, O_RDONLY);
    if(!check_extention(filename) || fd < 0)
                return(clean_exit(&map, 0, fd, "Error: where the file extention or file name is incorrect \n"), 0);
    if(!get_map_dimensions(fd, &map))
            return(clean_exit(&map, 0, fd, "Error: map dimensions are incorrect must be at least 3x3\n"), 0);
    close(fd);
    fd = open(filename, O_RDONLY);
    if(fd < 0 || !load_map(fd, &map))
        return(clean_exit(&map, 0, fd, "Error: Invalid element\n"), 0);
    close(fd);
    if(!validate_components(&map) || !is_map_closed(&map))
        return(clean_exit(&map, 0, -1, "Error: Invalid components\n"), 0);
}
