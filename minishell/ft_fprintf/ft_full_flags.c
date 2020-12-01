/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_full_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:40:43 by lryst             #+#    #+#             */
/*   Updated: 2020/12/01 12:29:29 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_just_flag(t_flags *prt, va_list args)
{
	if (prt->flags == 1)
		ft_flag_z(prt, args);
	if (prt->flags == 2)
		ft_flags_m(prt, args);
}

void	ft_full_flags_m(t_flags *prt, va_list args)
{
	unsigned long	u;
	size_t			swap;

	u = prt->c;
	prt->c = 0;
	ft_precision(prt, args);
	swap = prt->c;
	prt->c = u;
	u = swap;
	prt->c = prt->c + u;
	if (u < ((unsigned int)prt->nbr_f))
	{
		while (u++ < (unsigned int)prt->nbr_f)
			ft_putchar_c(' ', prt);
	}
}

void	ft_full_flags(t_flags *prt, va_list args)
{
	if (prt->flags == 2)
		ft_full_flags_m(prt, args);
	if (prt->flags == 1)
	{
		if (prt->nbr_f > prt->nbr_p)
		{
			(prt->conv == 1 || prt->conv == 2) ?
			ft_di_width_p(prt, args) : 0;
			prt->conv == 3 ? ft_u_width_p(prt, args) : 0;
			prt->conv == 4 ? ft_x_width_p(prt, args) : 0;
			prt->conv == 5 ? ft_maj_x_width_p(prt, args) : 0;
			prt->conv == 7 ? ft_s_w_p(prt, args) : 0;
		}
		else if (prt->nbr_f <= prt->nbr_p)
			ft_precision(prt, args);
	}
}
