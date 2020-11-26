/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_x.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:42:22 by lryst             #+#    #+#             */
/*   Updated: 2020/01/20 14:28:52 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_x_l(t_flags *prt, char q, va_list args)
{
	int				n;
	int				c;
	unsigned int	u;

	n = 0;
	u = va_arg(args, unsigned int);
	c = ft_hexa_len(u);
	if (u == 0 && prt->nbr_p == 0)
	{
		return ;
	}
	if (c < prt->nbr_f)
	{
		while (n + c < (prt->nbr_f))
		{
			ft_putchar_c(q, prt);
			n++;
		}
	}
	ft_putnbr_hexa(u, prt);
}

void	ft_x_right(t_flags *prt, va_list args)
{
	int				tmp;
	int				c;
	unsigned int	n;

	n = 0;
	tmp = prt->c;
	ft_putnbr_hexa(va_arg(args, unsigned int), prt);
	c = prt->c - tmp;
	while (n + c < ((unsigned int)prt->nbr_f))
	{
		ft_putchar_c(' ', prt);
		n++;
	}
}

void	ft_x_l_p(t_flags *prt, char q, va_list args)
{
	unsigned int	u;
	int				c;
	unsigned int	n;

	n = 0;
	u = va_arg(args, unsigned int);
	c = ft_hexa_len(u);
	if (u == 0 && prt->nbr_p == 0)
		return ;
	if (c < prt->nbr_p)
	{
		while (n + c < ((unsigned int)prt->nbr_p))
		{
			ft_putchar_c(q, prt);
			n++;
		}
	}
	ft_putnbr_hexa(u, prt);
}

void	ft_x_width_p2(t_flags *prt, int len)
{
	int i;

	i = 0;
	if (prt->nbr_p < len)
	{
		while (i++ < ((prt->nbr_f) - len))
			ft_putchar_c(' ', prt);
	}
	else if (prt->nbr_p >= len)
	{
		while (i++ < prt->nbr_f - prt->nbr_p)
			ft_putchar_c(' ', prt);
		i = 0;
		while (i++ < ((prt->nbr_p) - len))
			ft_putchar_c('0', prt);
	}
}

void	ft_x_width_p(t_flags *prt, va_list args)
{
	int				i;
	int				len;
	unsigned int	nbr;

	i = 0;
	nbr = va_arg(args, unsigned int);
	len = ft_hexa_len(nbr);
	if (nbr == 0 && prt->nbr_p == 0)
	{
		i = 0;
		while (i++ < prt->nbr_f)
			ft_putchar_c(' ', prt);
		return ;
	}
	if (prt->nbr_f > 0)
		ft_x_width_p2(prt, len);
	ft_putnbr_hexa(nbr, prt);
}
