/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oait-si- <oait-si-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:27:56 by oait-si-          #+#    #+#             */
/*   Updated: 2025/03/05 10:28:00 by oait-si-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#define ROWS 8
#define COLS 8

void floodFill(int screen[ROWS][COLS], int x, int y, int prevC, int newC) {
    // Base cases
    if (x < 0 || x >= ROWS || y < 0 || y >= COLS)
        return;
    if (screen[x][y] != prevC)
        return;

    // Replace the color at (x, y)
    screen[x][y] = newC;

    // Recur for north, east, south, and west
    floodFill(screen, x + 1, y, prevC, newC);
    floodFill(screen, x - 1, y, prevC, newC);
    floodFill(screen, x, y + 1, prevC, newC);
    floodFill(screen, x, y - 1, prevC, newC);
}

void printScreen(int screen[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++)
            printf("%d ", screen[i][j]);
        printf("\n");
    }
}

int main() {
    int screen[ROWS][COLS] = {
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 0, 0, 0, 1, 1, 1},
        {1, 0, 1, 1, 0, 1, 1, 1},
        {1, 0, 1, 1, 0, 1, 1, 1},
        {1, 0, 0, 0, 0, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1}
    };

    int x = 4, y = 4; // Starting point
    int newColor = 2;
    int prevColor = screen[x][y];
    floodFill(screen, x, y, prevColor, newColor);

    printScreen(screen);
    return 0;
}
