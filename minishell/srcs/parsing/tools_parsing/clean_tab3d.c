/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_tab3d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 09:46:59 by lryst             #+#    #+#             */
/*   Updated: 2020/11/23 09:51:29 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			clean_tab2d(char **tabin, char **tabout)
{
	int			i;
	int			k;

	k = 0;
	i = 0;
	while (tabin[i])
	{
		if (!ft_strcmp(tabin[i], " "))
		{
			ft_free(tabin[i]);
			ft_free(tabout[i]);
			i++;
		}
		else
		{
			tabin[k] = tabin[i];
			tabout[k++] = tabout[i++];
		}
	}
	tabin[k] = 0;
	tabout[k] = 0;
}

void			clean_tab2d_echo_2(int k, char **tabin, char **tabout)
{
	if (k > 0 && !ft_strcmp(tabin[k - 1], " "))
	{
		ft_free(tabin[k - 1]);
		ft_free(tabout[k - 1]);
		tabin[k - 1] = 0;
		tabout[k - 1] = 0;
	}
	else
	{
		tabin[k] = 0;
		tabout[k] = 0;
	}
}

void			clean_tab2d_echo(char **tabin, char **tabout)
{
	int			i;
	int			k;

	k = 0;
	i = 0;
	if (tabin[i])
	{
		if (!ft_strcmp(tabin[i], " "))
		{
			ft_free(tabin[i]);
			ft_free(tabout[i]);
			i++;
		}
		while (tabin[i])
		{
			tabin[k] = tabin[i];
			tabout[k++] = tabout[i++];
		}
		clean_tab2d_echo_2(k, tabin, tabout);
	}
}

void			clean_cpy_tab2d(char **cpy)
{
	int			i;
	int			k;

	k = 0;
	i = 0;
	if (cpy[i])
	{
		if (!ft_strcmp(cpy[i], " "))
			ft_free(cpy[i++]);
		while (cpy[i])
			cpy[k++] = cpy[i++];
		if (k > 0 && !ft_strcmp(cpy[k - 1], " "))
		{
			ft_free(cpy[k - 1]);
			cpy[k - 1] = 0;
		}
		else
			cpy[k] = 0;
	}
}

void			clean_split3d(t_temp *tmp)
{
	int			i;

	i = 0;
	while (tmp->inpipe[i])
	{
		if (cherche_echo(tmp->outpipe[i]))
			clean_tab2d_echo(tmp->inpipe[i], tmp->outpipe[i]);
		else
			clean_tab2d(tmp->inpipe[i], tmp->outpipe[i]);
		clean_cpy_tab2d(tmp->cpypipe[i]);
		i++;
	}
}
