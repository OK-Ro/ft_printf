#include "ft_printf.h"
#include <stdio.h>

int ft_printf_nbr(int n);



int main(int argc, char **argv)
{
    int i = 0;

    while (i < argc)
    {
        printf("argv[%d] = %s\n", i, argv[i]);
        i++;
    }

    printf("Total arguments (including program): %d\n", argc);
    printf("User arguments only: %d\n", argc - 1);

    return 0;
}