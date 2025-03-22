#include "mlx.h"
#include <stdio.h>





int main()
{
    void *mlx; //pointer to MLX connection 
    void *win; //pointer to window
    

    mlx  =  mlx_init();  // initialize the connection to the graphic system
    if(!mlx)
        printf("Error: mlx_init() failed.\n");
    win = mlx_new_window(mlx, 1900, 300, "doood"); // creates a new window 
    if(!win)
        printf("Error: mlx_");
    mlx_loop(mlx); // keeps the program running and waits for events (e.g., keypress, mouse, movement) 
}  