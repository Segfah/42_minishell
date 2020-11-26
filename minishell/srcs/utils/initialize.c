/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 14:00:14 by lryst             #+#    #+#             */
/*   Updated: 2020/11/25 18:23:30 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			initialize(t_temp *tmp, int *j)
{
	*j = 0;
	tmp->flag[1] = 0;
	tmp->flag[2] = 0;
	tmp->flag[3] = 0;
	tmp->tabpath = NULL;
	tmp->outpipe = NULL;
	tmp->inpipe = NULL;
	tmp->strcmd = NULL;
	tmp->strcmdin = NULL;
	tmp->cpytab = NULL;
	tmp->nb_pipes = 0;
}

void			initialize_tmp(t_temp *tmp, int ac, char **av)
{
	tmp->tab[0] = NULL;
	tmp->tab[1] = NULL;
	tmp->prompt = NULL;
	tmp->env = NULL;
	tmp->cpytab = NULL;
	tmp->tabcmd = NULL;
	tmp->strcmd = NULL;
	tmp->strcmdin = NULL;
	tmp->varenv = NULL;
	tmp->exportenv = NULL;
	tmp->tabpath = NULL;
	tmp->status = 0;
	tmp->fd = 0;
	tmp->fdi = 0;
	tmp->oldfd = 0;
	tmp->hnull = NULL;
	tmp->inpipe = NULL;
	tmp->outpipe = NULL;
	tmp->cpypipe = NULL;
	(void)ac;
	(void)av;
}
