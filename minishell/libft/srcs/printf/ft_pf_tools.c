/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 06:56:34 by corozco           #+#    #+#             */
/*   Updated: 2019/11/27 22:29:44 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_ini_node(t_ptf *node)
{
	node->maximus = 0;
	node->minus = 0;
	node->zero = 0;
	node->precision = 0;
	node->max = 0;
	node->min = 0;
	node->zer = 0;
	node->pre = 0;
	node->typ = 'e';
	node->tmp = 0;
	node->nul = 0;
}

int			ft_is_type(char c)
{
	return (c == 'c' || c == 's' || c == 'd' || c == 'i'
		|| c == 'p' || c == 'u' || c == 'x' || c == 'X' || c == '%');
}

int			ft_is_flag(char c)
{
	return (c == '.' || c == '-' || c == '*' || c == '0');
}

int			ft_putprintf(t_ptf *node, va_list ap)
{
	int	res;

	res = 0;
	if (node->typ == 'c' || node->typ == '%')
		res += ft_write_char(node, ap);
	if (node->typ == 's')
		res += ft_write_string(node, ap);
	if (node->typ == 'd' || node->typ == 'i' || node->typ == 'u')
		res += ft_write_number(node, ap, 0);
	if (node->typ == 'x' || node->typ == 'X')
		res += ft_write_hexa(node, ap);
	if (node->typ == 'p')
		res += ft_write_pointer(node, ap);
	return (res);
}
