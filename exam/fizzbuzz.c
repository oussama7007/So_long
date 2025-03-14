#include <stdio.h>
#include <unistd.h>

void ft_putnbr(int i)
{
    char c;
    if( n > 9)
        ft_putnbr( i / 10);
    c = (i % 10 ) + '0';
    write(1, &c, 1);
}


int main(void)
{
    int i = 0;
    if(i % 3 == 0 && i % 5 )
}