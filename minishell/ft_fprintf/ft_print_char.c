/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_char.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:41:23 by lryst             #+#    #+#             */
/*   Updated: 2020/01/20 14:36:36 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

int		*ft_print_m(int *u, t_flags *prt)
{
	ft_putchar_c('-', prt);
	*u = *u * (-1);
	return (u);
}

void	ft_putchar_c(char u, t_flags *prt)
{
	write(prt->fd, &u, 1);
	prt->c = prt->c + 1;
}

void	ft_putstr_c(char *str, t_flags *prt)
{
	int i;

	if (str == NULL)
	{
		ft_putstr_c("(null)", prt);
		return ;
	}
	i = pt_strlen(str);
	write(prt->fd, str, i);
	prt->c = prt->c + 1;
}

char	*ft_strcpy(char *dst, char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
