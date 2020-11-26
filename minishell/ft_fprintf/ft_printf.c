/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 13:42:29 by lryst             #+#    #+#             */
/*   Updated: 2020/01/20 14:28:52 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fprintf.h"

t_flags	fill_struct(t_flags *prt, int fd)
{
	prt->flags = 0;
	prt->nbr_f = -1;
	prt->p = 0;
	prt->nbr_p = -1;
	prt->conv = 0;
	prt->c = 0;
	prt->fd = fd;
	return (*prt);
}

int		ft_fprintf(int fd, const char *list, ...)
{
	va_list	args;
	t_flags prt;
	int		i;

	i = 0;
	va_start(args, list);
	fill_struct(&prt, fd);
	while (list[i])
	{
		if (list[i] == '%')
			ft_parse(list, &i, args, &prt);
		else
			ft_putchar_c(list[i], &prt);
		i++;
	}
	va_end(args);
	return (prt.c);
}
