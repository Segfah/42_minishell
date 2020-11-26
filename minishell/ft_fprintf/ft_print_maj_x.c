/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_maj_x.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:41:39 by lryst             #+#    #+#             */
/*   Updated: 2020/01/20 14:44:32 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_maj_x_truc(t_flags *prt, int len)
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
		while (i++ < ((prt->nbr_f - prt->nbr_p)))
			ft_putchar_c(' ', prt);
		i = 0;
		while (i++ < ((prt->nbr_p) - len))
			ft_putchar_c('0', prt);
	}
}

void	ft_maj_x_l(t_flags *prt, char q, va_list args)
{
	int				n;
	int				c;
	unsigned int	u;

	n = 0;
	u = va_arg(args, unsigned int);
	c = ft_hexa_len(u);
	if (u == 0 && prt->nbr_p == 0)
		return ;
	if (c < prt->nbr_f)
	{
		while ((n++) + c < (prt->nbr_f))
			ft_putchar_c(q, prt);
	}
	ft_putnbr_hexa_maj(u, prt);
}

void	ft_maj_x_right(t_flags *prt, va_list args)
{
	int				tmp;
	int				c;
	unsigned int	n;

	n = 0;
	tmp = prt->c;
	ft_putnbr_hexa_maj(va_arg(args, unsigned int), prt);
	c = prt->c - tmp;
	while (n + c < ((unsigned int)prt->nbr_f))
	{
		ft_putchar_c(' ', prt);
		n++;
	}
}

void	ft_maj_x_l_p(t_flags *prt, char q, va_list args)
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
		while ((n++) + c < ((unsigned int)prt->nbr_p))
			ft_putchar_c(q, prt);
	}
	ft_putnbr_hexa_maj(u, prt);
}

void	ft_maj_x_width_p(t_flags *prt, va_list args)
{
	int				i;
	int				len;
	unsigned int	nbr;

	i = 0;
	nbr = va_arg(args, unsigned int);
	len = ft_hexa_len(nbr);
	if (nbr == 0 && prt->nbr_p == 0)
	{
		while (i++ < prt->nbr_f)
			ft_putchar_c(' ', prt);
		return ;
	}
	if (prt->nbr_f > 0)
		ft_maj_x_truc(prt, len);
	ft_putnbr_hexa_maj(nbr, prt);
}
