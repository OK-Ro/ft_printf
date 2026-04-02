/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokuni <rokuni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 12:25:25 by rokuni            #+#    #+#             */
/*   Updated: 2026/04/02 19:13:47 by rokuni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_printf_hex_ptr(unsigned long n)
{
	const char	*base;
	int			count;

	count = 0;
	base = "0123456789abcdef";
	if (n >= 16)
		count += ft_printf_hex_ptr(n / 16);
	count += ft_printf_char(base[n % 16]);
	return (count);
}

int	ft_printf_ptr(void *ptr)
{
	unsigned long	newptr;
	int				count;

	if (!ptr)
		return (ft_printf_str("(nil)"));
	newptr = (unsigned long)ptr;
	count = ft_printf_str("0x");
	count += ft_printf_hex_ptr(newptr);
	return (count);
}