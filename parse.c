/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:00:51 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/04 18:26:35 by oait-si-         ###   ########.fr       */
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
int check_map_content(int fd)
{
    
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
    if(map_rectangilare(fd))
    if(check_map_content(fd) == 0)
        return (0);
    close(fd);    
}