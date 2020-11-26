/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:40:22 by lryst             #+#    #+#             */
/*   Updated: 2020/01/20 14:28:49 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_conv(t_flags *prt, va_list args)
{
	prt->conv == 1 ? ft_putnbrdi(va_arg(args, int), prt) : 0;
	prt->conv == 2 ? ft_putnbrdi(va_arg(args, int), prt) : 0;
	prt->conv == 3 ? ft_putnbru(va_arg(args, unsigned int), prt) : 0;
	prt->conv == 4 ? ft_putnbr_hexa(va_arg(args, unsigned int), prt) : 0;
	prt->conv == 5 ? ft_putnbr_hexa_maj(va_arg(args, unsigned int), prt)
	: 0;
	prt->conv == 6 ? ft_adres(va_arg(args, unsigned long long), prt) : 0;
	prt->conv == 7 ? ft_putstr_c(va_arg(args, char*), prt) : 0;
	prt->conv == 8 ? ft_putchar_c(va_arg(args, int), prt) : 0;
	prt->conv == 9 ? ft_putchar_c('%', prt) : 0;
}
