#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int ft_printf(const char *, ...);

/*internal helpers*/
int ft_printf_char(char c);
int ft_printf_str(char *s);
int ft_printf_ptr(void *ptr);
int ft_printf_nbr(int n);
int ft_printf_unit(unsigned int n);
int ft_printf_hex(unsigned int n, int uppercase);

#endif