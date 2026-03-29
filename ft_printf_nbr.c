/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokuni <rokuni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:41:39 by rokuni            #+#    #+#             */
/*   Updated: 2026/03/25 17:43:05 by rokuni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     ft_printf_nbr(int n)
{
	long	nbr;
	
	nbr = n;
	if (nbr < 0)
	{
		ft_printf_char('-');
		nbr = -nbr;
	}
	if (nbr >= 10)
		ft_printf_nbr(nbr / 10);
	ft_printf_char(nbr % 10 + '0');
	
}