/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rokuni <rokuni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 12:03:21 by rokuni            #+#    #+#             */
/*   Updated: 2026/03/31 14:12:28 by rokuni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <stdarg.h>
# include <stdlib.h>

int	ft_printf(const char *format, ...);

int	ft_printf_char(char c);
int	ft_printf_str(char *s);
int	ft_printf_nbr(int n);
int	ft_printf_unsigned(unsigned int n);
int	ft_printf_hex(unsigned long n, int uppercase);
int	ft_printf_ptr(void *ptr);

#endif