/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_pipes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:11:19 by lryst             #+#    #+#             */
/*   Updated: 2020/11/26 01:10:49 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "signal.h"

static void		pipes_status(t_temp *tmp, int *fd, int i)
{
	int			status;

	while (++i < tmp->nb_pipes + 1)
	{
		status = 0;
		wait(&status);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == 1)
			{
				free(fd);
				general_free(tmp);
			}
			if (i + 1 == tmp->nb_pipes + 1)
			{
				(WEXITSTATUS(status) == 0) ? g_ret = 0 : 0;
				(WEXITSTATUS(status) == 35) ? g_ret = 1 : 0;
				(WEXITSTATUS(status) == 126) ? g_ret = 126 : 0;
				(WEXITSTATUS(status) == 127) ? g_ret = 127 : 0;
				(WEXITSTATUS(status) == 255) ? g_ret = 255 : 0;
				(WEXITSTATUS(status) == 258) ? g_ret = 258 : 0;
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
