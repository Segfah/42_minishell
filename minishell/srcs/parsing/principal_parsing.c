/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principal_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:11:19 by lryst             #+#    #+#             */
/*   Updated: 2020/11/26 01:10:49 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pipes.h"

void			point_filename(char **tab)
{
	int			i;

	i = 0;
	while (tab[i])
		i++;
	if (i > 1)
		write(2, "minishell: Permission denied\n", 29);
	else
	{
		write(2, "minishell: .: filename argument required\n", 41);
		write(2, ".: usage: . filename [arguments]\n", 33);
	}
}

void			npipe(char **tabcmd, t_temp *tmp, t_cmd *cmd, int i)
{
	int			ret;
	int			j;

	j = 0;
	ret = (cmd) ? llist_astring(cmd, tmp) : 0;
	if (ret == -1)
	{
		cmd ? check_redi(tmp->strcmdin, tmp) : 0;
		general_free(tmp);
	}
	cmd ? check_redi(tmp->strcmdin, tmp) : 0;
	((tmp->flag[2] || tmp->flag[1]) && tmp->flag[2] != -1 && tmp->flag[1] != -1)
		? skip_redi(tmp, 0, 0) : 0;
	(tmp->strcmd) ? j = cmd_exist(tmp->strcmd[0], tmp, 0) : 0;
	tmp->flag[0] = (j > 0) ? 1 : 0;
	launcher_cmd(tabcmd[i], tmp, j, 0);
	ft_free_double_tab(tmp->strcmd);
	ft_free_double_tab(tmp->strcmdin);
	ft_free_double_tab(tmp->cpytab);
	tmp->flag[1] == 1 ? close(tmp->fd) : 0;
	tmp->flag[2] == 1 ? close(tmp->fdi) : 0;
}

int				no_cmd(int j, t_cmd *cmd, t_temp *tmp)
{
	if (j == -1)
	{
		(cmd != NULL) ? free_cmd(cmd) : 0;
		general_free(tmp);
	}
	if (j < 0)
	{
		(cmd != NULL) ? free_cmd(cmd) : 0;
		tmp->tabpath ? ft_free_tab(tmp->tabpath) : 0;
		return (1);
	}
	return (0);
}

static void		gestion_line(char **tabcmd, t_temp *tmp, int i)
{
	int			j;
	t_cmd		*cmd;

	if (error_line(tabcmd, tmp, i) == -1)
		return ;
	while (tabcmd[++i])
	{
		initialize(tmp, &j);
		cmd = NULL;
		separator_string(&cmd, tabcmd[i], tmp);
		ft_free_double_tab(tmp->strcmd);
		tmp->strcmd = NULL;
		(cmd) ? j = split3d(cmd, tmp) : 0;
		if (no_cmd(j, cmd, tmp) == 1)
			break ;
		(tmp->outpipe) ? gpipes(tmp, cmd, j) : npipe(tabcmd, tmp, cmd, i);
		(cmd != NULL) ? free_cmd(cmd) : 0;
		tmp->tabpath ? ft_free_tab(tmp->tabpath) : 0;
	}
}

int				ft_getline(t_temp *tmp, char **av, int ret)
{
	char		*line;

	if (av)
	{
		line = av[2];
		if ((tmp->tabcmd = ft_split_line(line)) == NULL)
			general_free(tmp);
		if (tmp->tabcmd != NULL && tmp->tabcmd[0])
			gestion_line(tmp->tabcmd, tmp, -1);
		ft_free_double_tab(tmp->tabcmd);
	}
	else
	{
		line = NULL;
		if ((ret = ft_gnl(0, &line)) == -1
			|| (tmp->tabcmd = ft_split_line(line)) == NULL)
			general_free(tmp);
		if (ret == 0)
			return (0);
		if (tmp->tabcmd != NULL && tmp->tabcmd[0])
			gestion_line(tmp->tabcmd, tmp, -1);
		ft_free_double_tab(tmp->tabcmd);
		ft_free(line);
	}
	return (1);
}
