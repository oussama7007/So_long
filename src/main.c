/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:53:58 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/22 01:16:24 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"
void f()
{
    //system("leaks so_long");
}
int main(int ac , char **av)
{
  t_game game;
   //atexit(f);
   ft_memset(&game, 0, sizeof(t_game));  
    if(ac != 2 )
    {
        ft_putstr_fd("Error: Enter only one map.ber\n", 2);
        return 1;
    }
    if(!validate_map(av[1], &game.map))
        return 0;
    ft_putstr_fd("Map is valid. Starting game...\n", 1);
    init_game(&game);
    mlx_loop(game.mlx);
    clean_exit_game(&game, NULL);
    return 0;
 
}
