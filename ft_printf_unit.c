/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokuni <rokuni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:42:45 by rokuni            #+#    #+#             */
/*   Updated: 2026/03/28 17:19:57 by rokuni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int     ft_printf_uint(unsigned int n)
{
	long	nb;
	nb = n;
	if (nb >= 10)
		ft_printf_uint(nb / 10);
	ft_printf_char(nb % 10 + '0');
}
