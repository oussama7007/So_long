/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*    game.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/16 01:33:07 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/16 04:21:05 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void clean_exit(t_game *game, char *msg)
{
    if(msg)
        perror(msg);
    if(game->win)
        mlx_destroy_window(gam->mlx, game->win);
    if(game->mlx)
    {
        mlx_destroy_dislplay(game->mlx);
        free(game->mlx);
    }
    clean_map(&game->map);
    exit(0);
}
void init_game(t_game *game)
{
    game->mlx = mlx_init();
    if(!game->mlx)
        
}