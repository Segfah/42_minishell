/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s_w_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:03:31 by lryst             #+#    #+#             */
/*   Updated: 2020/01/20 15:04:36 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_s_w_p2(t_flags *prt, int i, char *str)
{
	if (prt->nbr_p < 6)
	{
		while (i++ < ((prt->nbr_f) - (prt->nbr_p)))
			ft_putchar_c(' ', prt);
		i = -1;
		while (++i < prt->nbr_p)
			ft_putchar_c(str[i], prt);
	}
	else if (prt->nbr_p >= 6)
	{
		i = 0;
		while (i++ < ((prt->nbr_f - prt->nbr_p)))
			ft_putchar_c(' ', prt);
		i = 0;
		while (i++ < ((prt->nbr_p) - 6))
			ft_putchar_c(' ', prt);
		ft_putstr_c(str, prt);
	}
}

void	ft_s_w_p3(t_flags *prt, int i, char *str)
{
	int len;

	len = pt_strlen(str);
	if (prt->nbr_p < len)
	{
		while (i++ < ((prt->nbr_f) - (prt->nbr_p)))
			ft_putchar_c(' ', prt);
		i = -1;
		while (++i < prt->nbr_p)
			ft_putchar_c(str[i], prt);
	}
	else if (prt->nbr_p >= len)
	{
		i = 0;
		while (i++ < ((prt->nbr_f - prt->nbr_p)))
			ft_putchar_c(' ', prt);
		i = 0;
		while (i++ < ((prt->nbr_p) - len))
			ft_putchar_c(' ', prt);
		ft_putstr_c(str, prt);
	}
}

void	ft_s_w_p(t_flags *prt, va_list args)
{
	int		i;
	char	*str;
	char	*null;

	i = 0;
	str = va_arg(args, char*);
	null = "(null)";
	if (str != NULL)
		ft_s_w_p3(prt, i, str);
	if (str == NULL)
		ft_s_w_p2(prt, i, null);
}
