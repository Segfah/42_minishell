/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:54:38 by lryst             #+#    #+#             */
/*   Updated: 2020/11/29 19:03:32 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_llintlen(int n)
{
	long long int		len;

	if (n == 2147482647)
		return (11);
	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void		gestion_exit(char **strcmd, t_temp *tmp, int key)
{
	if (!strcmd[1] && !key)
	{
		g_ret = 0;
		write(1, "exit\n", 5);
		exit(g_ret);
	}
	else
	{
		if ((ft_intlen(ft_atoi(strcmd[1])) == (int)ft_strlen(strcmd[1]) ||
		ft_strcmp(strcmd[1], "-9223372036854775808") == 0) &&
		(tmp->cpytab[3] == NULL || !ft_strcmp(tmp->cpytab[3], " ")))
			exit_arg(strcmd, key);
		else
			exit_join(tmp->strcmd, key);
	}
}

void		exit_join(char **tab, int key)
{
	g_ret = 255;
	if (!key)
		write(1, "exit\n", 5);
	write(2, "minishell: exit: ", 17);
	write(2, tab[1], ft_strlen(tab[1]));
	write(2, ": numeric argument required\n", 28);
	exit(g_ret);
}

void		exit_arg(char **strcmd, int key)
{
	if (strcmd[2])
	{
		g_ret = 1;
		if (!key)
			write(1, "exit\n", 5);
		write(2, "minishell: exit: too many arguments\n", 36);
	}
	else
	{
		g_ret = ft_atoi((const char*)strcmd[1]);
		write(1, "exit\n", 5);
		exit(g_ret);
	}
}
