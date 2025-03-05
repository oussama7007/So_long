/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:00:51 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/05 09:53:00 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int   check_extention(char *str)
{
    int j = 0;
    int i;
    i = 0;
    
    char *s = "reb.";
    while(str[i])
        i++;
    if(i < 4)
        return 0;
    while(j <= 3)
    {
          if(str[--i] != s[j])
               return 0;
           j++;
    }
    return 1;
}
int check_lines(int fd)
{
    int i;
    int line;
    char *map;
    map = get_next_line(fd);
    if(!map)
        return 0;
    int size = ft_strlen(map);
    while(map)
    {
        if(size != ft_strlen(map))
            return 0;
        free(map);
        map = get_next_line(fd);   
    }
    free(map);
    return 1;
}
int map_rectangilare(int fd)
{
    
    char *map = get_next_line(fd);
    int size = ft_strlen(map);
    int i  = 0;
    while(map)
    {
        free(map);
        map = get_next_line(fd);
        i++;
    }
    if(size == i)
        return 0;
    return 1;
}
int  is_valid_char(char c)
{
    return(c == '0' || c == '1' || c == 'C' || c == 'E' || c == 'P');
}
void free_map(char **map, int height)
{
    int i;
    
    i = -1;
    while(++i < height)
        free(map[i]);
    free(map);
}
int check_map_content(int fd)
{
    char **map NULL;
    
    
}
int validate_map(char *str)
{
    int fd;
    char *map;
    if (check_extention(str) == 0)
        return(0);
    fd = open(str, O_RDWR);
    if(fd == -1)
        return (0);
    if(check_lines(fd) == 0)
        return (0);
    if(map_rectangilare(fd) == 0)
        return (0);
    if(check_map_content(fd) == 0)
        return (0);
    close(fd);    
}