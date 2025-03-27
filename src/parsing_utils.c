/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 02:02:42 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/25 11:51:21 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_strdup(char *str)
{
	char	*new;
	int		i;
	int		size;

	size = ft_strlen(str);
	i = -1;
	new = malloc(size + 1);
	if (!new)
		return (NULL);
	while (++i < size)
		new[i] = str[i];
	new[i] = '\0';
	return (new);
}

void	clean_map(t_map *map)
{
	int	i;

	i = -1;
	if (map->grid)
	{
		while (++i < map->height)
			free(map->grid[i]);
		free(map->grid);
		map->grid = NULL;
	}
}

void	clean_exit(t_map *map, int fd, char *str)
{
	if (map)
		clean_map(map);
	if (str)
		ft_putstr_fd(str, 2);
	if (fd > 0)
		close(fd);
}

void	*ft_memset(void *str, int value, size_t len)
{
	unsigned char	*p;
	size_t			i;

	p = (unsigned char *)str;
	i = 0;
	while (i < len)
	{
		p[i] = (unsigned char)value;
		i++;
	}
	return (str);
}

void	free_dubel(char **str, int height)
{
	int	i;

	i = -1;
	while (++i < height)
		free(str[i]);
	free(str);
}
