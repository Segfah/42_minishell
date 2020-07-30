/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 08:17:49 by corozco           #+#    #+#             */
/*   Updated: 2019/11/27 22:36:07 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static int	ft_start(char *str, va_list ap)
{
	t_ptf	node;
	int		res;

	res = 0;
	ft_ini_node(&node);
	str = ft_check_max(str, ap, &node);
	node.min = (node.max < 0) ? -node.max : 0;
	node.minus = (node.min != 0) ? 1 : 0;
	while (ft_isdigit(*str) || ft_is_flag(*str) || ft_is_type(*str))
	{
		str = (*str == '-') ? ft_check_min(str, ap, &node) : str;
		str = (*str == '0') ? ft_check_zero(str, ap, &node) : str;
		str = (*str == '.') ? ft_check_pres(str, ap, &node) : str;
		if (ft_is_type(*str))
		{
			node.typ = *str;
			break ;
		}
	}
	res = ft_putprintf(&node, ap);
	return (res);
}

static int	ft_engine(char *str, va_list ap, int *count, int i)
{
	int		tmp;

	tmp = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1] == '%')
		{
			*count += ft_putchar('%');
			i++;
		}
		else if (str[i] == '%')
		{
			if (((tmp = ft_start(&str[i + 1], ap)) == -1))
				return (-1);
			*count += tmp;
			i++;
			while ((!ft_is_type(str[i]) && (ft_isdigit(str[i])
							|| ft_is_flag(str[i]))))
				++i;
		}
		else
			*count += ft_putchar(str[i]);
		i++;
	}
	return (*count);
}

int			ft_printf(const char *format, ...)
{
	va_list	ap;
	int		res;

	res = 0;
	if (*format)
	{
		va_start(ap, format);
		res = ft_engine((char *)format, ap, &res, 0);
		if (res == -1)
			return (-1);
		va_end(ap);
	}
	return (res);
}
