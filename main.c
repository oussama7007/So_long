/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:53:58 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/14 21:15:59 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"
#include <stdio.h>
#include <stdlib.h>
#include "mlx.h"
int main(int ac , char **av)
{
    if(ac != 2 )
      return 0;
    if(validate_map(av[1]) == 0)
    {
        write(1, "Error\n", 6);
        return 0;
    }

    return 0;
 
}
