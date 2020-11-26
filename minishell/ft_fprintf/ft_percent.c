/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:41:07 by lryst             #+#    #+#             */
/*   Updated: 2020/01/20 14:28:52 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_percent_right(t_flags *prt)
{
	int n;

	n = 0;
	ft_putchar_c('%', prt);
	while (n++ < ((prt->nbr_f) - 1))
		ft_putchar_c(' ', prt);
}

void	ft_percent_left(t_flags *prt, char q)
{
	int n;

	n = 0;
	while (n++ < ((prt->nbr_f) - 1))
		ft_putchar_c(q, prt);
	ft_putchar_c('%', prt);
}
