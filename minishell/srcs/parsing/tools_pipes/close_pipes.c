/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:11:19 by lryst             #+#    #+#             */
/*   Updated: 2020/12/01 12:33:49 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msignal.h"

static void		pipes_signal_free(int *fd, t_temp *tmp)
{
	free(fd);
	general_free(tmp);
}

static void		pipes_status(t_temp *tmp, int *fd, int i)
{
	int			status;
	int			macro;

	while (++i < tmp->nb_pipes + 1)
	{
		status = 0;
		wait(&status);
		if (WIFEXITED(status))
		{
			macro = WEXITSTATUS(status);
			if (macro == 1)
				pipes_signal_free(fd, tmp);
			if (i + 1 == tmp->nb_pipes + 1)
			{
				(macro == 0) ? g_ret = 0 : 0;
				(macro == 35) ? g_ret = 1 : 0;
				(macro == 126) ? g_ret = 126 : 0;
				(macro == 127) ? g_ret = 127 : 0;
				(macro == 255) ? g_ret = 255 : 0;
				(macro == 258) ? g_ret = 258 : 0;
			}
		}
	}
}

void			close_gpipes(t_temp *tmp, int *fd)
{
	pipes_status(tmp, fd, -1);
	signal(SIGINT, sighandler);
	free(fd);
	ft_free_triple_tab(tmp->inpipe);
	ft_free_triple_tab(tmp->outpipe);
	ft_free_triple_tab(tmp->cpypipe);
}
