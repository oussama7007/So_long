#include <stdio.h>
#include <stdlib.h>

// Custom ft_memset implementation.
void *ft_memset(void *str, int value, size_t len)
{
    unsigned char *p;
    size_t i;

    p = (unsigned char *)str;
    i = 0;
    while (i < len)
    {
        p[i] = (unsigned char)value;
        i++;
    }
    return str;
}

int main(void)
{
    int arr[10];
    int i;

    // Initialize the array with values 1 through 10.
    for (i = 0; i < 10; i++)
        arr[i] = i + 1;

    // Print the original array.
    printf("Original array: ");
    for (i = 0; i < 10; i++)
        printf("%d ", arr[i]);
    printf("\n");

    /* 
     * Use ft_memset to set all bytes of the array to 0.
     * Since each int typically occupies sizeof(int) bytes,
     * we need to fill (10 * sizeof(int)) bytes.
     */
    ft_memset(arr, 0, 4 * 10 );

    // Print the modified array.
    printf("Modified array: ");
    for (i = 0; i < 10; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
