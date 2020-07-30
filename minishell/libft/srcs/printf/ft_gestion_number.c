/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gestion_number.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 03:43:25 by corozco           #+#    #+#             */
/*   Updated: 2019/11/27 22:29:12 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_write_number_minus(t_ptf *node, char *str)
{
	int		res;
	int		len;
	int		i;

	i = 0;
	res = ft_strlen(str);
	node->pre = (str[0] == '-') ? node->pre + 1 : node->pre;
	len = (node->pre >= res) ? node->pre : res;
	res = (len >= node->min) ? len : node->min;
	if (str[i] == '-')
		ft_putchar(str[i++]);
	node->tmp = i;
	while (node->pre > (int)ft_strlen(str))
	{
		i += ft_putchar('0');
		node->pre--;
	}
	if (str[node->tmp] == '0' && node->precision == 1 && node->pre == 0)
		i += ft_putstr("");
	else
		i += ft_putstr(&str[node->tmp]);
	while (i < res)
		i += ft_putchar(' ');
	return (res);
}

int			ft_write_number_max(t_ptf *node, char *str)
{
	int		res;
	int		len;
	int		i;

	i = 0;
	res = ft_strlen(str);
	node->pre = (str[0] == '-') ? node->pre + 1 : node->pre;
	len = (node->pre >= res) ? node->pre : res;
	res = (len >= node->max) ? len : node->max;
	while (i < res - len)
	{
		ft_putchar(' ');
		i++;
	}
	i = (str[0] != '-') ? 0 : -1;
	node->tmp = 0;
	while (++i <= len - (int)ft_strlen(str))
	{
		if (str[node->tmp] == '-')
			ft_putchar(str[node->tmp++]);
		else
			ft_putchar('0');
	}
	ft_putstr(&str[node->tmp]);
	return (res);
}

int			ft_write_number_zero(t_ptf *node, char *str)
{
	int		res;
	int		i;

	i = 0;
	node->tmp = 0;
	res = ft_strlen(str);
	res = (res >= node->zer) ? res : node->zer;
	if (str[i] == '-')
		node->tmp = ft_putchar(str[i]);
	while (i < res - (int)ft_strlen(str))
		i += ft_putchar('0');
	ft_putstr(&str[node->tmp]);
	return (res);
}

int			ft_write_number_zero_pres(t_ptf *node, char *str)
{
	int		res;
	int		len;
	int		i;

	i = 0;
	res = ft_strlen(str);
	node->pre = (str[0] == '-') ? node->pre + 1 : node->pre;
	len = (node->pre >= res) ? node->pre : res;
	res = (len >= node->zer) ? len : node->zer;
	while (i < res - len)
		i += ft_putchar(' ');
	i = (str[0] != '-') ? 0 : -1;
	node->tmp = 0;
	while (++i <= len - (int)ft_strlen(str))
	{
		if (str[node->tmp] == '-')
			ft_putchar(str[node->tmp++]);
		else
			ft_putchar('0');
	}
	ft_putstr(&str[node->tmp]);
	return (res);
}

int			ft_write_number(t_ptf *node, va_list ap, int res)
{
	char	*nb;
	long	var;

	if (node->typ == 'u')
		var = (unsigned int)va_arg(ap, unsigned int);
	else
		var = (int)va_arg(ap, int);
	if (var == 0 && node->precision == 1 && node->precision != 0)
		nb = ft_strdup("");
	else
		nb = ft_ltoa(var);
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
