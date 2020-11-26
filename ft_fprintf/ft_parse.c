/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:41:00 by lryst             #+#    #+#             */
/*   Updated: 2020/01/20 14:43:22 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

t_flags	*ft_is_stars(int *i, t_flags *prt, va_list args)
{
	int stars;

	stars = va_arg(args, int);
	if (stars < 0)
	{
		prt->flags = 2;
		stars = -stars;
	}
	prt->nbr_f = stars;
	*i = *i + 1;
	return (prt);
}

t_flags	*ft_is_p(const char *str, int *i, t_flags *prt, va_list args)
{
	int stars;

	stars = 0;
	prt->p = 1;
	*i = *i + 1;
	if (str[*i] == '*')
	{
		stars = va_arg(args, int);
		prt->nbr_p = stars;
		*i = *i + 1;
	}
	else if (str[*i] != '*')
	{
		(prt->nbr_p = ft_count_nbr(str, i));
		if (prt->nbr_p == -1)
			prt->nbr_p = 0;
	}
	return (prt);
}

t_flags	*ft_is_flags(const char *str, int *i, t_flags *prt)
{
	while (str[*i] == '0' || str[*i] == '-')
	{
		if (str[*i] == '0')
		{
			prt->flags = 1;
			*i = *i + 1;
		}
		if (str[*i] == '-')
		{
			prt->flags = 2;
			while (str[*i] == '0' || str[*i] == '-')
				*i = *i + 1;
		}
	}
	return (prt);
}

t_flags	*ft_parse_conv(const char *str, int *i, t_flags *prt)
{
	str[*i] == 'd' ? prt->conv = 1 : 0;
	str[*i] == 'i' ? prt->conv = 2 : 0;
	str[*i] == 'u' ? prt->conv = 3 : 0;
	str[*i] == 'x' ? prt->conv = 4 : 0;
	str[*i] == 'X' ? prt->conv = 5 : 0;
	str[*i] == 'p' ? prt->conv = 6 : 0;
	str[*i] == 's' ? prt->conv = 7 : 0;
	str[*i] == 'c' ? prt->conv = 8 : 0;
	str[*i] == '%' ? prt->conv = 9 : 0;
	return (prt);
}

void	ft_parse(const char *str, int *i, va_list args, t_flags *prt)
{
	(*i)++;
	ft_is_flags(str, i, prt);
	if (str[*i] == '*')
		ft_is_stars(i, prt, args);
	if (str[*i] > '0' && str[*i] <= '9')
		prt->nbr_f = ft_count_nbr(str, i);
	if (prt->flags != 0 && prt->nbr_f == -1)
		prt->nbr_f = 0;
	if (str[*i] == '.')
		ft_is_p(str, i, prt, args);
	ft_parse_conv(str, i, prt);
	ft_check_struct(prt, args);
}
