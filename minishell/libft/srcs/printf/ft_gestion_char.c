/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gestion_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 04:13:35 by corozco           #+#    #+#             */
/*   Updated: 2019/11/26 04:56:12 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_write_char_minus(t_ptf *node, int c)
{
	int		res;

	res = 0;
	res += ft_putchar(c);
	while (res < node->min)
		res += ft_putchar(' ');
	return (res);
}

static int	ft_write_char_zero(t_ptf *node, int c)
{
	int		res;

	res = 0;
	while (res < node->zer - 1)
		res += ft_putchar('0');
	res += ft_putchar(c);
	return (res);
}

static int	ft_write_char_max(t_ptf *node, int c)
{
	int		res;

	res = 0;
	while (res < node->max - 1)
		res += ft_putchar(' ');
	res += ft_putchar(c);
	return (res);
}

int			ft_write_char(t_ptf *node, va_list ap)
{
	int		res;
	char	c;

	if (node->typ == '%')
		c = '%';
	else
		c = va_arg(ap, int);
	res = 0;
	if (node->minus == 1)
		res += ft_write_char_minus(node, c);
	else if (node->zero == 1 && ft_is_type(node->typ))
		res += ft_write_char_zero(node, c);
	else if (node->maximus == 1)
		res += ft_write_char_max(node, c);
	else
		res += ft_putchar(c);
	return (res);
}
