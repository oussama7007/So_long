/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:53:58 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/02 15:52:23 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>


int main(int ac , char **av)
{
      void *mlx = mlx_init();
      if(!mlx) 
        exit(1);

      
      void *win = mlx_new_window(mlx, 800, 600, "my first window");
      if (!parse_map(av[1]))
        return (0);
      if(!win)
        exit(1);

      mlx_loop(mlx);
}
