/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:41:13 by lryst             #+#    #+#             */
/*   Updated: 2020/01/20 14:31:08 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_precision(t_flags *prt, va_list args)
{
	void				*a;
	unsigned long long	nbr;

	nbr = 0;
	(prt->conv == 1 || prt->conv == 2) ?
	ft_di_left_p(prt, '0', args) : 0;
	prt->conv == 3 ? ft_u_left_p(prt, '0', args) : 0;
	prt->conv == 4 ? ft_x_l_p(prt, '0', args) : 0;
	prt->conv == 5 ? ft_maj_x_l_p(prt, '0', args) : 0;
	prt->conv == 7 ? ft_s_lz_p(prt, args) : 0;
	prt->conv == 9 ? ft_putchar_c('%', prt) : 0;
	if (prt->conv == 6 && prt->p == 1 && prt->nbr_p == 0 && prt->nbr_f == -1
	&& prt->flags == 0)
	{
		a = va_arg(args, void*);
		nbr = (unsigned long long)(a);
		if (a == NULL)
		{
			ft_putstr_c("0x", prt);
			return ;
		}
		ft_adres(nbr, prt);
	}
}
