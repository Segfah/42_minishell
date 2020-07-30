/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pf_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 07:01:15 by corozco           #+#    #+#             */
/*   Updated: 2019/11/28 02:04:30 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_check_wid(char *str, va_list ap, t_ptf *node)
{
	if (*str == '*')
	{
		while (*str == '*')
		{
			node->tmp = va_arg(ap, int);
			str++;
		}
	}
	return (str);
}

char		*ft_check_max(char *str, va_list ap, t_ptf *node)
{
	char	tab[12];
	int		i;

	while (*str == '*')
	{
		node->maximus = 1;
		str = ft_check_wid(str, ap, node);
		node->max = node->tmp;
	}
	if (ft_isdigit(*str) && *str != '0')
	{
		node->maximus = 1;
		i = 0;
		while (ft_isdigit(*str))
			tab[i++] = *str++;
		tab[i] = '\0';
		node->max = ft_atoi(tab);
	}
	while (*str == '*')
	{
		node->maximus = 1;
		str = ft_check_wid(str, ap, node);
		node->max = node->tmp;
	}
	return (str);
}

char		*ft_check_min(char *str, va_list ap, t_ptf *node)
{
	char	tab[12];
	int		i;

	node->minus = 1;
	str++;
	if (*str != '\0' && ft_isdigit(*str))
	{
		i = 0;
		while (ft_isdigit(*str))
			tab[i++] = *str++;
		tab[i] = '\0';
		node->min = ft_atoi(tab);
	}
	while (*str == '*')
	{
		str = ft_check_wid(str, ap, node);
		node->min = (node->tmp < 0) ? -node->tmp : node->tmp;
	}
	return (str);
}

char		*ft_check_pres(char *str, va_list ap, t_ptf *node)
{
	char	tab[12];
	int		i;

	node->precision = 1;
	str++;
	if (*str != '\0' && ft_isdigit(*str))
	{
		i = 0;
		while (ft_isdigit(*str))
			tab[i++] = *str++;
		tab[i] = '\0';
		node->pre = ft_atoi(tab);
	}
	while (*str == '*')
	{
		str = ft_check_wid(str, ap, node);
		node->pre = node->tmp;
	}
	node->pre = (node->pre < 0) ? -1 : node->pre;
	node->precision = (node->pre == -1) ? 0 : 1;
	return (str);
}

char		*ft_check_zero(char *str, va_list ap, t_ptf *node)
{
	char	tab[12];
	int		i;

	node->zero = 1;
	str++;
	if (*str != '\0' && ft_isdigit(*str))
	{
		i = 0;
		while (ft_isdigit(*str))
			tab[i++] = *str++;
		tab[i] = '\0';
		node->zer = ft_atoi(tab);
	}
	while (*str == '*')
	{
		str = ft_check_wid(str, ap, node);
		node->zer = node->tmp;
	}
	return (str);
}
