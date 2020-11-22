/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 14:00:14 by lryst             #+#    #+#             */
/*   Updated: 2020/11/22 18:24:35 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			initialize(t_temp *tmp, int *j)
{
	*j = 0;
	tmp->flag[1] = 0;
	tmp->flag[2] = 0;
	tmp->tabpath = NULL;
	tmp->outpipe = NULL;
	tmp->inpipe = NULL;
	tmp->strcmd = NULL;
	tmp->strcmdin = NULL;
	tmp->cpytab = NULL;
}

void			initialize_tmp(t_temp *tmp, int ac, char **av)
{
	tmp->env = NULL;
	tmp->prompt = NULL;
	tmp->varenv = NULL;
	tmp->exportenv = NULL;
	tmp->env = NULL;
	tmp->tab[0] = NULL;
	tmp->tab[1] = NULL;
	tmp->hnull = NULL;
	tmp->strcmd = NULL;
	tmp->strcmdin = NULL;
	(void)ac;
	(void)av;
}
