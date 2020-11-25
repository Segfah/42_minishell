/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 17:27:31 by lryst             #+#    #+#             */
/*   Updated: 2020/11/25 18:49:23 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		echo_join(char **tabin, char **tabout)
{
	int i;

	i = 0;
	write(2, "minishell: ", 11);
	while (tabin[i] && tabout[i] && ft_strcmp(tabin[i], " "))
	{
		write(2, tabout[i], ft_strlen(tabout[i]));
		i++;
	}
	write(2, ": command not found\n", 20);
}

void		gestion_echo_2(t_temp *tmp, int n, int i)
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

void		gestion_echo(t_temp *tmp, int key)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	dup_or_not(tmp);
	if (echo_cote_space(tmp, key) == 0)
	{
		(tmp->flag[1] == 1) ? dup2(tmp->oldfd, 1) : 0;
		return ;
	}
	i = 2;
	if (!check_multi_options(tmp, &i, &n))
		return ;
	gestion_echo_2(tmp, n, i);
	(tmp->flag[1] == 1) ? dup2(tmp->oldfd, 1) : 0;
}

int			check_echo_2(int *check, int *i, char c, char *s)
{
	if (s && s[*i] && (s[*i] == c || s[*i] == c - 40))
	{
		*check += 1;
		(*i)++;
		return (*check);
	}
	*check = 0;
	return (0);
}
