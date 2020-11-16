/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 17:27:31 by lryst             #+#    #+#             */
/*   Updated: 2020/11/06 19:59:14 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_check_option_echo(char *s)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(s);
	if (s[i] == '-')
	{
		if (s[i + 1])
			i++;
		while (s[i] && s[i] == 'n')
			i++;
	}
	if (i == len)
		return (i);
	return (0);
}

void	gestion_echo_2(t_temp *tmp, int n, int i)
{
	while (tmp->strcmd[i])
	{
		ft_printf("%s", tmp->strcmd[i]);
		i++;
	}
	g_ret = 0;
	if (n == 0)
		ft_printf("\n");
}

void	gestion_echo(t_temp *tmp)
{
	int		i;
	int		n;

	i = 0;
	if (tmp->flag[1] == 1)
	{
		tmp->oldfd = dup(1);
		dup2(tmp->fd, 1);
	}
	n = 0;
	if (tmp->strcmd[i + 1] != NULL)
		i++;
	else
		n = 1;
	if (tmp->strcmd[i + 1] != NULL)
		i++;
	if (ft_check_option_echo(tmp->strcmd[i]) != 0)
	{
		i++;
		if (tmp->strcmd[i + 1] != NULL)
			i++;
		n = 2;
	}
	if (n == 1)
	{
		write(1, "\n", 1);
		(tmp->flag[1] == 1) ? dup2(tmp->oldfd, 1) : 0;
		return ;
	}
	gestion_echo_2(tmp, n, i);
	(tmp->flag[1] == 1) ? dup2(tmp->oldfd, 1) : 0;
}
