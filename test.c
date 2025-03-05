/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:27:56 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/05 17:58:17 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#define ROWS 3
#define COLS 3


void floodfill(int screen[ROWS][COLS], int x, int y, int prevC, int newC)
{
    if(x < 0 || y < 0 || x >= COLS || y >= ROWS)
        return ;
    
    screen[x][y] = newC;

    floodfill(screen, x + 1, y , prevC, newC);
    floodfill(screen, x - 1, y , prevC, newC);
    floodfill(screen, x, y - 1 , prevC, newC);
    floodfill(screen, x, y + 1 , prevC, newC);
    
}
void printfscreen(int screen[ROWS][COLS])
{
    int  i = 0 ;
    int j = 0;
    while (i < COLS)
    {
        j = 0;
        while (j < ROWS)
        {
            printf("%d",screen[i][j] );
            j++;
        }
        i++;
    }
    
}
int main(void)
{
    int screen[ROWS][COLS] = {
        {1,5,9},
        {1,2,6},
        {4,1,5},
    };
    int x = 0;
    int y = 0;
    int newColor = 1;
    int prevColor = screen[x][y];
    floodfill(screen, x, y, prevColor, newColor);
    printfscreen(screen);
    return 0;
}