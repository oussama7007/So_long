/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:53:58 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/15 19:49:50 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"


void f()
{
    system("leaks so_long");
}
int main(int ac , char **av)
{
    atexit(f);
    if(ac != 2 )
      return 0;
    if(validate_map(av[1]) == 0)
    {
        write(1, "Error\n", 6);
        return 0;
    }

    return 0;
 
}
