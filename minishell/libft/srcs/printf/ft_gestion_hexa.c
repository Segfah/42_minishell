/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gestion_hexa.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 21:17:10 by corozco           #+#    #+#             */
/*   Updated: 2019/11/27 22:27:34 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_write_hexa(t_ptf *node, va_list ap)
{
	int		res;
	char	*nb;
	long	var;

	res = 0;
	var = va_arg(ap, unsigned);
	if (var == 0 && node->precision == 1 && node->precision != 0)
		nb = ft_strdup("");
	else
		nb = (node->typ == 'x') ? ft_itoa_base(var, 16, 'a')
			: ft_itoa_base(var, 16, 'A');
	if (!nb)
		return (-1);
	if (node->minus == 1)
		res += ft_write_number_minus(node, nb);
	else if (node->zero == 1 && node->precision == 0)
		res += ft_write_number_zero(node, nb);
	else if (node->zero == 1 && node->precision == 1)
		res += ft_write_number_zero_pres(node, nb);
	else if (node->precision == 1 || node->maximus == 1)
		res += ft_write_number_max(node, nb);
	else
		res += ft_putstr(nb);
	free(nb);
	return (res);
}
