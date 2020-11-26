/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_nbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:41:44 by lryst             #+#    #+#             */
/*   Updated: 2020/01/20 14:37:01 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

void	ft_putnbr_hexa(unsigned int n, t_flags *prt)
{
	if (n > 15)
	{
		ft_putnbr_hexa((n / 16), prt);
		ft_putnbr_hexa((n % 16), prt);
	}
	else if (n < 10)
		ft_putchar_c(n + '0', prt);
	else
		ft_putchar_c(n - 10 + 'a', prt);
}

void	ft_putnbru(unsigned int n, t_flags *prt)
{
	if (n > 9)
	{
		ft_putnbru(n / 10, prt);
		ft_putnbru(n % 10, prt);
	}
	else
		ft_putchar_c(n + 48, prt);
}

void	ft_putnbrdi(int n, t_flags *prt)
{
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		prt->c = prt->c + 11;
	}
	else
	{
		if (n < 0)
		{
			ft_putchar_c('-', prt);
			n = n * -1;
		}
		if (n > 9)
		{
			ft_putnbrdi(n / 10, prt);
			ft_putnbrdi(n % 10, prt);
		}
		else
			ft_putchar_c(n + 48, prt);
	}
}

void	ft_putnbr_hexa_maj(unsigned int n, t_flags *prt)
{
	if (n > 15)
	{
		ft_putnbr_hexa_maj((n / 16), prt);
		ft_putnbr_hexa_maj((n % 16), prt);
	}
	else if (n < 10)
		ft_putchar_c(n + '0', prt);
	else
		ft_putchar_c(n - 10 + 'A', prt);
}

void	ft_putnbr_p(unsigned long long n, t_flags *prt)
{
	if (n > 15)
	{
		ft_putnbr_p((n / 16), prt);
		ft_putnbr_p((n % 16), prt);
	}
	else if (n < 10)
		ft_putchar_c(n + '0', prt);
	else
		ft_putchar_c(n - 10 + 'a', prt);
}
