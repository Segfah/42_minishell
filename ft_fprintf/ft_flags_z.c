/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_z.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:40:38 by lryst             #+#    #+#             */
/*   Updated: 2020/01/20 14:31:08 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_flag_z(t_flags *prt, va_list args)
{
	prt->conv == 1 ? ft_di_left(prt, '0', args) : 0;
	prt->conv == 2 ? ft_di_left(prt, '0', args) : 0;
	prt->conv == 3 ? ft_u_left(prt, '0', args) : 0;
	prt->conv == 4 ? ft_x_l(prt, '0', args) : 0;
	prt->conv == 5 ? ft_maj_x_l(prt, '0', args) : 0;
	prt->conv == 9 ? ft_percent_left(prt, '0') : 0;
}
