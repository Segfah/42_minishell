/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gestion_string.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 05:04:51 by corozco           #+#    #+#             */
/*   Updated: 2019/11/27 22:33:08 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_write_string_minus(t_ptf *node, char *str)
{
	int	res;
	int	len;
	int	i;

	i = 0;
	res = ft_strlen(str);
	if (node->precision == 1)
		len = (node->pre <= res) ? node->pre : res;
	else
		len = res;
	res = (len >= node->min) ? len : node->min;
	while (i < res)
	{
		if (len > 0)
		{
			len--;
			ft_putchar(str[i]);
		}
		else
			ft_putchar(' ');
		i++;
	}
	return (res);
}

static int	ft_write_string_max_pres(t_ptf *node, char *str)
{
	int	res;
	int	len;
	int	i;

	i = 0;
	res = ft_strlen(str);
	len = (node->pre <= res) ? node->pre : res;
	res = (len >= node->max) ? len : node->max;
	while (i < res - len)
	{
		ft_putchar(' ');
		i++;
	}
	while (len > 0)
	{
		ft_putchar(*str++);
		len--;
	}
	return (res);
}

static int	ft_write_string_max(t_ptf *node, char *str)
{
	int	res;

	res = 0;
	node->max -= ft_strlen(str);
	while (node->max-- > 0)
		res += ft_putchar(' ');
	res += ft_putstr(str);
	return (res);
}

int			ft_write_string(t_ptf *node, va_list ap)
{
	int		res;
	char	*str;

	res = 0;
	str = va_arg(ap, char *);
	if (str == NULL)
	{
		node->nul = 1;
		str = ft_strdup("(null)");
	}
	if (!str)
		return (-1);
	if (node->minus == 1)
		res += ft_write_string_minus(node, str);
	else if (node->maximus == 1 && node->precision == 0)
		res += ft_write_string_max(node, str);
	else if (node->precision == 1)
		res += ft_write_string_max_pres(node, str);
	else
		res += ft_putstr(str);
	if (node->nul == 1)
		free(str);
	return (res);
}
