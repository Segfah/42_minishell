/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:44:44 by corozco           #+#    #+#             */
/*   Updated: 2020/11/29 18:18:17 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int		ft_atoi(const char *str)
{
	long long nb;
	long long nega;

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
