/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:00:51 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/09 03:03:06 by oait-si-         ###   ########.fr       */
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
int clean_exit(t_map *map, int status, int fd)
{
    if(map) clean_map(map);
    if(fd > 0) close(fd);
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
    map->whidth = first_line_len;
    return(map->height > 2 && map > 2);
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

Copy
int	process_line(t_map *map, char *line, int y)
{
	size_t	len;
	int		x;

	if (!line || !(map->grid[y] = ft_strdup(line)))
		return (0);
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
int     load_map(char *filename, t_map *map)
{
    int fd;
    char *line;
    int y;

    fd = open(filename, O_RDONLY);
    if(fd < 0 || !init_map_storage(map))
        return 0;
    y = -1;
    while( ++y < map->height)
    {
        line = get_next_line(fd);
        if(!process_line(map, line, y))
        {
            free(line);
            return(clean_map(map, y), close(fd), 0);
        }
        free(line);
    }
    free(line);
    return 1;
}
int validate_map(char *filename)
{
    int fd;
    t_map map;

    map = {0};
    fd = open(filename, O_RDONLY);
    if(!check_extention(filename) || fd < 0)
        return(clean_exit(NULL, 0, fd));
    if(!get_map_dimensions(fd &map))
        return (clean_exit(NULL, 0, fd));
    close(fd);
    fd = open(filename, O_RDONLY);
    if(!load_map(fd, &map))
        return(clean_exit(NULL, 0, fd))
    close(fd);
}
