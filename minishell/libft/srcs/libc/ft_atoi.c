/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:44:44 by corozco           #+#    #+#             */
/*   Updated: 2019/10/18 07:14:41 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long nb;
	long nega;

	nb = 0;
	nega = 1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
		*str++ == '-' ? nega = -nega : nega;
	while (*str && *str <= '9' && *str >= '0')
	{
		nb = nb * 10 + (*str++ - 48);
		if (nb < 0 && nega == 1)
			return (-1);
		if (nb < 0 && nega == -1)
			return (0);
	}
	return (nb * nega);
}
