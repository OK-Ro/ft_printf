#include <stdio.h>
#include "ft_printf.h"

int main(void)
{
    int     n;
    char    c;
    char    *str;
    void    *p;

    // Basic pointer
    n = 42;
    printf("printf:    %p\n", &n);
    ft_printf("ft_printf: %p\n", &n);

    // Char pointer
    c = 'a';
    printf("printf:    %p\n", &c);
    ft_printf("ft_printf: %p\n", &c);

    // String pointer
    str = "hello";
    printf("printf:    %p\n", str);
    ft_printf("ft_printf: %p\n", str);

    // NULL
    printf("printf:    %p\n", NULL);
    ft_printf("ft_printf: %p\n", NULL);

    // Pointer to pointer
    p = &n;
    printf("printf:    %p\n", &p);
    ft_printf("ft_printf: %p\n", &p);

    // Stack vs heap
    p = malloc(1);
    printf("printf:    %p\n", p);
    ft_printf("ft_printf: %p\n", p);
    free(p);

    return (0);
}