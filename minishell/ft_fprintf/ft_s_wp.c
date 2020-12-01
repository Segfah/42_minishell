/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s_wp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:06:18 by lryst             #+#    #+#             */
/*   Updated: 2020/12/01 12:30:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_s_wp2(t_flags *prt, char *str)
{
	int i;

	i = -1;
	if (6 >= (prt->nbr_p))
	{
		while (++i < (prt->nbr_p))
			ft_putchar_c(str[i], prt);
	}
	else if (6 < (prt->nbr_p))
	{
		if (6 < prt->nbr_f)
		{
			while (++i < (prt->nbr_f - 6))
				ft_putchar_c(' ', prt);
		}
		ft_putstr_c(str, prt);
	}
}

void	ft_s_wp3(t_flags *prt, int len, char *str)
{
	int i;

	i = -1;
	if (len >= (prt->nbr_p))
	{
		if (len <= prt->nbr_f)
		{
			while (++i < (prt->nbr_f - len))
				ft_putchar_c(' ', prt);
		}
		i = -1;
		while (++i < (prt->nbr_p))
			ft_putchar_c(str[i], prt);
	}
	else if (len < (prt->nbr_p))
	{
		if (len <= prt->nbr_f)
		{
			while (++i < (prt->nbr_f - len))
				ft_putchar_c(' ', prt);
		}
		ft_putstr_c(str, prt);
	}
}

void	ft_s_wp(t_flags *prt, va_list args)
{
	char	*str;
	int		len;
	char	*null;

	len = 0;
	str = va_arg(args, char *);
	null = "(null)";
	if (str == NULL)
		ft_s_wp2(prt, null);
	else
	{
		len = pt_strlen(str);
		ft_s_wp3(prt, len, str);
	}
}
