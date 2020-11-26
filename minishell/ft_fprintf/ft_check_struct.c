/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:40:15 by lryst             #+#    #+#             */
/*   Updated: 2020/01/20 14:28:48 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_check_struct2(t_flags *prt, va_list args)
{
	if (prt->flags != 0 && prt->nbr_f >= 0 &&
	prt->p != 0 && prt->nbr_p < 0 && prt->conv != 0)
		ft_just_flag(prt, args);
	if (prt->flags == 0 && prt->nbr_f == -1 &&
	prt->p != 0 && prt->nbr_p < 0 && prt->conv != 0)
		ft_conv(prt, args);
	if (prt->flags == 0 && prt->nbr_f == -1 &&
	prt->p == 0 && prt->nbr_p < 0 && prt->conv != 0)
		ft_conv(prt, args);
	if (prt->flags != 0 && prt->nbr_f >= 0 &&
	prt->p == 0 && prt->nbr_p < 0 && prt->conv != 0)
		ft_just_flag(prt, args);
	if (prt->flags == 0 && prt->nbr_f == -1 &&
	prt->p != 0 && prt->nbr_p >= 0 && prt->conv != 0)
		ft_precision(prt, args);
}

void	ft_check_struct(t_flags *prt, va_list args)
{
	if (prt->flags == 0 && prt->nbr_f >= 0 &&
	prt->p != 0 && prt->nbr_p < 0 && prt->conv != 0)
		ft_width(prt, args);
	if (prt->flags == 0 && prt->nbr_f >= 0 &&
	prt->p == 0 && prt->nbr_p < 0 && prt->conv != 0)
		ft_width(prt, args);
	if (prt->flags != 0 && prt->nbr_f >= 0 &&
	prt->p != 0 && prt->nbr_p >= 0 && prt->conv != 0)
		ft_full_flags(prt, args);
	if (prt->flags == 0 && prt->nbr_f >= 0 &&
	prt->p != 0 && prt->nbr_p >= 0 && prt->conv != 0)
		ft_width_p(prt, args);
	if (prt->flags != 0 && prt->nbr_f == -1 &&
	prt->p == 0 && prt->nbr_p < 0 && prt->conv != 0)
		ft_conv(prt, args);
	ft_check_struct2(prt, args);
}
