/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_widths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:42:54 by lryst             #+#    #+#             */
/*   Updated: 2020/01/20 14:53:30 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_width(t_flags *prt, va_list args)
{
	prt->conv == 1 ? ft_di_left(prt, ' ', args) : 0;
	prt->conv == 2 ? ft_di_left(prt, ' ', args) : 0;
	prt->conv == 3 ? ft_u_left(prt, ' ', args) : 0;
	prt->conv == 4 ? ft_x_l(prt, ' ', args) : 0;
	prt->conv == 5 ? ft_maj_x_l(prt, ' ', args) : 0;
	prt->conv == 6 ? ft_p_left(prt, ' ', args) : 0;
	prt->conv == 7 ? ft_s_l_space(prt, ' ', args) : 0;
	prt->conv == 8 ? ft_c_left(prt, ' ', args) : 0;
	prt->conv == 9 ? ft_percent_left(prt, ' ') : 0;
}

void	ft_width_p(t_flags *prt, va_list args)
{
	if (prt->nbr_f > prt->nbr_p)
	{
		prt->conv == 1 ? ft_di_width_p(prt, args) : 0;
		prt->conv == 2 ? ft_di_width_p(prt, args) : 0;
		prt->conv == 3 ? ft_u_width_p(prt, args) : 0;
		prt->conv == 4 ? ft_x_width_p(prt, args) : 0;
		prt->conv == 5 ? ft_maj_x_width_p(prt, args) : 0;
		prt->conv == 7 ? ft_s_w_p(prt, args) : 0;
		prt->conv == 6 ? ft_p_left(prt, ' ', args) : 0;
	}
	if (prt->nbr_f <= prt->nbr_p && prt->conv == 7 &&
	prt->nbr_f > 0 && prt->nbr_p > 0)
		ft_s_wp(prt, args);
	else if (prt->nbr_f <= prt->nbr_p)
		ft_precision(prt, args);
}
