/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gestion_pointer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 20:44:40 by corozco           #+#    #+#             */
/*   Updated: 2019/11/27 22:32:12 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_write_pointer_minus(t_ptf *node, char *str)
{
	int		res;
	int		len;
	int		i;

	i = 0;
	res = ft_strlen(str) + 2;
	len = (node->pre >= res) ? node->pre : res;
	res = (len >= node->min) ? len : node->min;
	node->tmp = i;
	ft_putstr("0x");
	while (node->pre > ((int)ft_strlen(str) + 2))
	{
		i += ft_putchar('0');
		node->pre--;
	}
	i += ft_putstr(&str[node->tmp]);
	while (i + 2 < res)
		i += ft_putchar(' ');
	return (res);
}

static int	ft_write_pointer_max(t_ptf *node, char *str)
{
	int		res;
	int		len;
	int		i;

	i = 0;
	res = ft_strlen(str) + 2;
	len = (node->pre >= res) ? node->pre : res;
	res = (len >= node->max) ? len : node->max;
	while (i < res - len)
	{
		ft_putchar(' ');
		i++;
	}
	i = 0;
	node->tmp = 0;
	while (++i <= len - ((int)ft_strlen(str) + 2))
		ft_putchar('0');
	ft_putstr("0x");
	ft_putstr(&str[node->tmp]);
	return (res);
}

static int	ft_write_pointer_zero(t_ptf *node, char *str)
{
	int		res;
	int		i;

	i = 0;
	node->tmp = 0;
	res = ft_strlen(str) + 2;
	res = (res >= node->zer) ? res : node->zer;
	while (i < res - ((int)ft_strlen(str) + 2))
		i += ft_putchar('0');
	ft_putstr(&str[node->tmp]);
	return (res);
}

static int	ft_write_pointer_zero_pres(t_ptf *node, char *str)
{
	int		res;
	int		len;
	int		i;

	i = 0;
	res = ft_strlen(str) + 2;
	len = (node->pre >= res) ? node->pre : res;
	res = (len >= node->zer) ? len : node->zer;
	while (i < res - len)
		i += ft_putchar(' ');
	i = -1;
	node->tmp = 0;
	while (++i <= len - ((int)ft_strlen(str) + 2))
		ft_putchar('0');
	ft_putstr(&str[node->tmp]);
	return (res);
}

int			ft_write_pointer(t_ptf *node, va_list ap)
{
	int		res;
	char	*nb;
	long	var;

	res = 0;
	var = va_arg(ap, size_t);
	if (var == 0 && node->precision == 1 && node->precision != 0)
		nb = ft_strdup("");
	else
		nb = ft_itoa_base(var, 16, 'a');
	if (!nb)
		return (-1);
	if (node->minus == 1)
		res += ft_write_pointer_minus(node, nb);
	else if (node->zero == 1 && node->precision == 0)
		res += ft_write_pointer_zero(node, nb);
	else if (node->zero == 1 && node->precision == 1)
		res += ft_write_pointer_zero_pres(node, nb);
	else if (node->precision == 1 || node->maximus == 1)
		res += ft_write_pointer_max(node, nb);
	else
		res += ft_printf("0x%s", nb);
	free(nb);
	return (res);
}
