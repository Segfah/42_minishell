/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/27 13:54:38 by lryst             #+#    #+#             */
/*   Updated: 2020/11/27 13:54:39 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			gestion_exit(char **strcmd, t_temp *tmp, int key)
{
	if (!strcmd[1] && !key)
	{
		g_ret = 0;
		write(1, "exit\n", 5);
		exit (g_ret);
	}
	else
	{
		if (ft_intlen(ft_atoi(strcmd[1])) == (int)ft_strlen(strcmd[1]) &&
		(tmp->cpytab[3] == NULL || !ft_strcmp(tmp->cpytab[3], " ")))
			exit_arg(strcmd, key);
		else
			exit_join(tmp->strcmd);
	}
}

void			exit_join(char **tab)
{
	g_ret = 255;
	write(1, "exit\n", 5);
	write(2, "minishell: exit: ", 17);
	write(2, tab[1], ft_strlen(tab[1]));
	write(2, ": numeric argument required\n", 28);
	exit(g_ret);
}

void			exit_arg(char **strcmd, int key)
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
