/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokuni <rokuni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 12:25:00 by rokuni            #+#    #+#             */
/*   Updated: 2026/03/31 13:59:27 by rokuni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_str(char *s)
{
	int	count;

	if (!s)
		s = "(null)";
	count = 0;
	while (*s)
	{
		count += ft_printf_char(*s);
		s++;
	}
	return (count);
}
