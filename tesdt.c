#include <stdio.h>
 typedef struct s_struct {
    int x;
    int y;
    int p;
} t_struct;

void    print(t_struct  c)
{
    printf("%d/%d", c.x, c.y);
}

int main() {
    print((t_struct){77 ,   5, 888});
}
