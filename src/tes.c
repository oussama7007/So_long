#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
char *ft_strdup(void)
{
    char *map = malloc(7);
    if(!map)
        return NULL;
    return map;
}

int main(void)
{
    char srr[] = "1234567";
    char *map;
    int i = 0;
    map = ft_strdup();
    while(i < 10)
    {
        map[i] = srr[i]  ;
        i++;
        
    }
    map[i] = '\0'; 
    printf("%s\n", map);
    return 0;
}