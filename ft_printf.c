/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokuni <rokuni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 10:51:29 by rokuni            #+#    #+#             */
/*   Updated: 2026/03/31 14:15:14 by rokuni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	print_format(char format_type, va_list args)
{
	int	printed_chars;

	printed_chars = 0;
	if (format_type == 'c')
		printed_chars += ft_printf_char(va_arg(args, int));
	else if (format_type == 's')
		printed_chars += ft_printf_str(va_arg(args, char *));
	else if (format_type == 'd' || format_type == 'i')
		printed_chars += ft_printf_nbr(va_arg(args, int));
	else if (format_type == 'p')
    	printed_chars += ft_printf_ptr(va_arg(args, void *));
	else if (format_type == 'u')
		printed_chars += ft_printf_unsigned(va_arg(args, unsigned int));
	else if (format_type == 'x')
		printed_chars += ft_printf_hex((unsigned long)va_arg(args, unsigned int), 0); 
	else if (format_type == 'X')
		printed_chars += ft_printf_hex((unsigned long)va_arg(args, unsigned int), 1); 
	else if (format_type == '%')
		printed_chars += ft_printf_char('%');
	return (printed_chars);
}

int	ft_printf(const char *format, ...)
{
	int		printed_chars;
	va_list	args;

	va_start(args, format);
	printed_chars = 0;
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (*format == '\0')
				break ;
			printed_chars += print_format(*format, args);
		}
		else
			printed_chars += ft_printf_char(*format);
		format++;
	}
	va_end(args);
	return (printed_chars);
}

