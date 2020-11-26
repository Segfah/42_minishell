/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_di.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:41:28 by lryst             #+#    #+#             */
/*   Updated: 2020/01/20 14:46:33 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_di_truc(t_flags *prt, int len, int nbr)
{
	int i;

	i = 0;
	if (nbr >= 0)
	{
		while (i++ < ((prt->nbr_f - prt->nbr_p)))
			ft_putchar_c(' ', prt);
		i = 0;
		while (i++ < ((prt->nbr_p) - len))
			ft_putchar_c('0', prt);
	}
	if (nbr < 0)
	{
		while (i++ < ((prt->nbr_f - prt->nbr_p) - 1))
			ft_putchar_c(' ', prt);
		ft_putchar_c('-', prt);
		nbr = -nbr;
		i = 0;
		while (i++ < ((prt->nbr_p) - len + 1))
			ft_putchar_c('0', prt);
	}
	ft_putnbrdi(nbr, prt);
}

void	ft_di_left(t_flags *prt, char q, va_list args)
{
	int u;
	int c;
	int n;

	n = 0;
	u = va_arg(args, int);
	c = ft_intlen(u);
	if (u == 0 && prt->nbr_f == 0 && prt->p != 0 && prt->nbr_p == 0)
	{
		while (n++ < prt->nbr_f)
			ft_putchar_c(' ', prt);
		return ;
	}
	if (u < 0 && prt->flags == 1)
		ft_print_m(&u, prt);
	while (n++ < ((prt->nbr_f) - c))
		ft_putchar_c(q, prt);
	if (u < 0 && prt->flags == 0)
		ft_print_m(&u, prt);
	ft_putnbrdi(u, prt);
}

void	ft_di_right(t_flags *prt, va_list args)
{
	int u;
	int n;
	int c;

	n = 0;
	u = va_arg(args, int);
	c = ft_intlen(u);
	ft_putnbrdi(u, prt);
	while (n++ < ((prt->nbr_f) - c))
		ft_putchar_c(' ', prt);
}

void	ft_di_left_p(t_flags *prt, char q, va_list args)
{
	int nbr;
	int len;
	int i;

	i = 0;
	nbr = va_arg(args, int);
	len = ft_intlen(nbr);
	if (nbr == 0 && prt->nbr_p == 0)
		return ;
	if (nbr >= 0)
	{
		while (i++ < ((prt->nbr_p) - len))
			ft_putchar_c(q, prt);
	}
	if (nbr < 0)
	{
		ft_putchar_c('-', prt);
		nbr = nbr * (-1);
		while (i++ < ((prt->nbr_p) - (len - 1)))
			ft_putchar_c(q, prt);
	}
	ft_putnbrdi(nbr, prt);
}

void	ft_di_width_p(t_flags *prt, va_list args)
{
	int len;
	int nbr;
	int i;

	i = 0;
	nbr = va_arg(args, int);
	len = ft_intlen(nbr);
	if (nbr == 0 && prt->nbr_p == 0)
	{
		i = 0;
		while (i++ < prt->nbr_f)
			ft_putchar_c(' ', prt);
		return ;
	}
	if (prt->nbr_p >= len)
		ft_di_truc(prt, len, nbr);
	if (prt->nbr_p < len)
	{
		while (i++ < ((prt->nbr_f) - len))
			ft_putchar_c(' ', prt);
		ft_putnbrdi(nbr, prt);
	}
}
