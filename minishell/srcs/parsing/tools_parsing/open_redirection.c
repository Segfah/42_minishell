/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:58:48 by corozco           #+#    #+#             */
/*   Updated: 2020/11/25 17:23:29 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_redi(char *str)
{
	return (!(ft_strcmp(">", str)) || !(ft_strcmp(">>", str))
		|| !(ft_strcmp("<", str)));
}

static int	simple_redi(char *path, t_temp *tmp)
{
	(tmp->fd > 0) ? close(tmp->fd) : 0;
	tmp->fd = 0;
	if ((tmp->fd = open(path, O_RDWR | O_TRUNC |
			O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		ft_fprintf(2, "minishell: %s: %s\n", path, strerror(errno));
		g_ret = 1;
		return (-1);
	}
	return (0);
}

static int	double_redi(char *path, t_temp *tmp)
{
	(tmp->fd > 0) ? close(tmp->fd) : 0;
	tmp->fd = 0;
	if ((tmp->fd = open(path, O_APPEND | O_WRONLY | O_CREAT, 0644)) == -1)
	{
		ft_fprintf(2, "minishell: %s: %s\n", path, strerror(errno));
		g_ret = 1;
		return (-1);
	}
	return (0);
}

static int	contre_redi(char *path, t_temp *tmp)
{
	(tmp->fdi > 0) ? close(tmp->fdi) : 0;
	tmp->fdi = 0;
	if ((tmp->fdi = open(path, O_RDONLY)) == -1)
	{
		ft_fprintf(2, "minishell: %s: %s\n", path, strerror(errno));
		g_ret = 1;
		return (-1);
	}
	return (0);
}

int			check_redi_flag2(char **cmd, t_temp *tmp, int *i)
{
	if (!(ft_strcmp(">", cmd[*i])))
	{
		tmp->flag[1] = 1;
		!ft_strcmp(cmd[*i + 1], " ") ? (*i)++ : *i;
		if (tmp->flag[2] != -1
			&& simple_redi(tmp->strcmd[*i + 1], tmp) == -1)
			return (tmp->flag[1] = -1);
	}
	else if (tmp->flag[2] != -1 && !(ft_strcmp(">>", cmd[*i])))
	{
		tmp->flag[1] = 1;
		!ft_strcmp(cmd[*i + 1], " ") ? (*i)++ : *i;
		if (double_redi(tmp->strcmd[*i + 1], tmp) == -1)
			return (tmp->flag[1] = -1);
	}
	else if (!(ft_strcmp("<", cmd[*i])))
	{
		tmp->flag[2] = 1;
		!ft_strcmp(cmd[*i + 1], " ") ? (*i)++ : *i;
		if (contre_redi(tmp->strcmd[*i + 1], tmp) == -1)
			return (tmp->flag[2] = -1);
	}
	return (0);
}
