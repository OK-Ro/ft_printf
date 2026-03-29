#include "ft_printf.h"
#include <stdio.h>

static int handle_format_specifier(char specifier, va_list args)
{
	int printed_chars = 0;


	 if (specifier == 'd' || specifier == 'i')
		printed_chars += ft_printf_nbr(va_arg(args, int));
	return printed_chars;
}

int ft_printf(const char *format, ...)
{
	va_list args;
	int printed_chars = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			printed_chars += handle_format_specifier(*format, args);
		}
		else
			printed_chars += ft_printf_char(*format);
		format++;
	}
	va_end(args);

	return printed_chars;
}

int main()
{
	ft_printf("Hello, %s! This is a number: %d\n", "world", 42);
	printf("Hello, %s! This is a number: %d\n", "world", 42);
	return 0;
}

