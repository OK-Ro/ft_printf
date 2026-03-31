/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokuni <rokuni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 12:24:47 by rokuni            #+#    #+#             */
/*   Updated: 2026/03/31 14:00:28 by rokuni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf_unsigned(unsigned int n)
{
	long	nb;
	int		count;

	count = 0;
	nb = n;
	if (nb > 10)
		count += ft_printf_unsigned(nb / 10);
	count += ft_printf_char(nb % 10 + '0');
	return (count);
}
