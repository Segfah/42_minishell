/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 02:39:33 by corozco           #+#    #+#             */
/*   Updated: 2019/11/25 20:09:09 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_ltoa(long n)
{
	long	i;
	long	sign;
	long	tmp;
	char	*str;

	tmp = (n < 0) ? -(long)n : n;
	sign = (n < 0) ? -1 : 0;
	i = (sign == -1) ? 2 : 1;
	while ((tmp /= 10) >= 1)
		i++;
	if (!(str = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	str[i] = '\0';
	tmp = (n < 0) ? -(long)n : n;
	while (i-- + sign)
	{
		str[i] = tmp % 10 + '0';
		tmp /= 10;
	}
	(i == 0) ? str[i] = '-' : 0;
	return (str);
}
