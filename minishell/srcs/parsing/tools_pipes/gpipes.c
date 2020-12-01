/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gpipes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:11:19 by lryst             #+#    #+#             */
/*   Updated: 2020/12/01 12:25:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msignal.h"
#include "pipes.h"

static void		open_dup(int *fd, t_temp *tmp)
{
	int			i;

	i = 0;
	while (i < tmp->nb_pipes)
	{
		if (pipe(fd + i * 2) < 0)
		{
			ft_fprintf(2, "error dup\n");
			exit(0);
		}
		i++;
	}
}

static void		close_dup(int *fd, t_temp *tmp)
{
	int			i;

	i = 0;
	while (i < tmp->nb_pipes * 2)
	{
		close(fd[i]);
		i++;
	}
}

static void		cmd_pipes(t_temp *tmp, int j, t_fdpipes *var, t_cmd *cmd)
{
	if (var->k != 0)
		dup2(var->fd[var->s - 2], 0);
	if (tmp->outpipe[var->k + 1] != NULL)
		dup2(var->fd[var->s + 1], 1);
	close_dup(var->fd, tmp);
	tmp->strcmd = tmp->outpipe[var->k];
	tmp->strcmdin = tmp->inpipe[var->k];
	tmp->cpytab = tmp->cpypipe[var->k];
	cmd ? check_redi(tmp->strcmdin, tmp) : 0;
	((tmp->flag[2] || tmp->flag[1]) && tmp->flag[2] != -1 && tmp->flag[1] != -1)
		? skip_redi(tmp, 0, 0) : 0;
	(tmp->strcmd) ? j = cmd_exist(tmp->strcmd[0], tmp, 0) : 0;
	tmp->flag[0] = (j > 0) ? 1 : 0;
	launcher_cmd(tmp->outpipe[var->k][0], tmp, j, 1);
	tmp->flag[1] == 1 ? close(tmp->fd) : 0;
	tmp->flag[2] == 1 ? close(tmp->fdi) : 0;
	if (g_ret == 1)
		exit(35);
	exit(g_ret);
}

void			gpipes(t_temp *tmp, t_cmd *cmd, int j)
{
	pid_t		pid;
	t_fdpipes	var;

	if (!(var.fd = malloc(sizeof(int) * tmp->nb_pipes * 2)))
		general_free(tmp);
	open_dup(var.fd, tmp);
	var.k = 0;
	var.s = 0;
	while (tmp->outpipe[var.k])
	{
		if ((pid = fork()) == 0)
			cmd_pipes(tmp, j, &var, cmd);
		else
		{
			signal(SIGINT, sighandler5);
			signal(SIGQUIT, sighandler3);
			var.s += 2;
			var.k++;
		}
	}
	close_dup(var.fd, tmp);
	close_gpipes(tmp, var.fd);
}
