/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_m.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:40:32 by lryst             #+#    #+#             */
/*   Updated: 2020/01/20 14:28:52 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_flags_m(t_flags *prt, va_list args)
{
	prt->conv == 1 ? ft_di_right(prt, args) : 0;
	prt->conv == 2 ? ft_di_right(prt, args) : 0;
	prt->conv == 3 ? ft_u_right(prt, args) : 0;
	prt->conv == 4 ? ft_x_right(prt, args) : 0;
	prt->conv == 5 ? ft_maj_x_right(prt, args) : 0;
	prt->conv == 6 ? ft_p_right(prt, args) : 0;
	prt->conv == 7 ? ft_s_right(prt, args) : 0;
	prt->conv == 8 ? ft_c_right(prt, args) : 0;
	prt->conv == 9 ? ft_percent_right(prt) : 0;
}
