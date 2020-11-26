/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:42:01 by lryst             #+#    #+#             */
/*   Updated: 2020/01/20 14:44:57 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_s_l_space(t_flags *prt, char q, va_list args)
{
	int		i;
	int		len;
	char	*str;

	i = 0;
	str = va_arg(args, char*);
	if (str == NULL)
	{
		while (i++ < ((prt->nbr_f) - 6))
			ft_putchar_c(q, prt);
		ft_putstr_c("(null)", prt);
	}
	if (str != NULL)
	{
		len = pt_strlen(str);
		while (i++ < ((prt->nbr_f) - len))
			ft_putchar_c(q, prt);
		ft_putstr_c(str, prt);
	}
}

void	ft_s_right(t_flags *prt, va_list args)
{
	int		i;
	char	*str;

	str = va_arg(args, char*);
	if (str != NULL)
	{
		i = pt_strlen(str);
		ft_putstr_c(str, prt);
		while (i++ < (prt->nbr_f))
			ft_putchar_c(' ', prt);
	}
	else
	{
		i = 6;
		ft_putstr_c("(null)", prt);
		while (i++ < (prt->nbr_f))
			ft_putchar_c(' ', prt);
	}
}

void	ft_s_lz(t_flags *prt, va_list args)
{
	int		u;
	char	*s;
	int		c;

	u = 0;
	s = va_arg(args, char*);
	c = pt_strlen(s);
	if (c > (prt->nbr_f))
	{
		while (u++ < (prt->nbr_f))
			ft_putchar_c(s[u], prt);
	}
	else if (c < (prt->nbr_f))
		ft_putstr_c(s, prt);
}
