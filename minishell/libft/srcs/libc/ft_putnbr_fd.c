/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:13:49 by corozco           #+#    #+#             */
/*   Updated: 2019/10/07 17:19:36 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int nn;

	if (n >= 0)
		nn = (unsigned int)n;
	else
	{
		ft_putchar_fd('-', fd);
		nn = n * -1;
	}
	if (nn > 10)
	{
		ft_putnbr_fd(nn / 10, fd);
		ft_putchar_fd(nn % 10 + 48, fd);
	}
	else
		ft_putchar_fd(nn % 10 + 48., fd);
}
