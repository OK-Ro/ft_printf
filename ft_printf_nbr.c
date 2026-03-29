/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokuni <rokuni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:41:39 by rokuni            #+#    #+#             */
/*   Updated: 2026/03/29 15:57:32 by rokuni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     ft_printf_nbr(int n)
{
	long	nb;
	nb = n;
	if (nb < 0)
	{
		ft_printf_char('-');
		nb = -nb;
	}
	if (nb >= 10)
		ft_printf_nbr(nb / 10);
	ft_printf_char(nb % 10 + '0');
}
