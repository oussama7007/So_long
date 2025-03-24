/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 08:25:20 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/24 16:34:08 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		i;
	int		j;

	i = -1;
	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	res = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (NULL);
	while (s1[++i] != '\0')
		res[i] = s1[i];
	j = -1;
	while (s2[++j] != '\0')
		res[i++] = s2[j];
	res[i] = '\0';
	return (res);
}

char	*ft_strchr(const char *string, int searched_char)
{
	while (*string != (char)searched_char && *string != '\0')
		string++;
	if (*string == (char)searched_char)
		return ((char *)string);
	return (NULL);
}

size_t	ft_strlen(const char *the_string)
{
	size_t	i;

	i = 0;
	while (the_string[i])
		i++;
	return (i);
}

void	ft_putnbr(int nb)
{
	int	a;

	if (nb >= 10)
		ft_putnbr(nb / 10);
	a = nb % 10 + '0';
	write(1, &a, 1);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}
