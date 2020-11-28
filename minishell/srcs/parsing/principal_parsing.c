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

void			printftab(char **tab)
{
	int			i;

	i = -1;
	if (tab)
	{
		ft_printf("----printtab----\n");
		while (tab[++i])
			ft_printf("---[%d], --- [%s]\n", i, tab[i]);
		ft_printf("-----------------\n");
	}
}

void			printflist(t_cmd *cmd)
{
	t_cmd		*tmp;

	tmp = cmd;
	ft_printf("----printlist----\n");
	while (tmp)
	{
		ft_printf("list in[%s] out[%s]\n", tmp->input, tmp->output);
		tmp = tmp->next;
	}
	ft_printf("-----------------\n");
}

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

void			open_dup(int *fd, t_temp *tmp)
{
	int			i;

	i = 0;
	while (i < tmp->nb_pipes)
	{
		if (pipe(fd + i * 2) < 0)
		{
			ft_fprintf(2,"error dup\n");
			exit(0);
		}
		i++;
	}
}

void			close_dup(int *fd, t_temp *tmp)
{
	int			i;

	i = 0;
	while (i < tmp->nb_pipes * 2)
	{
		close(fd[i]);
		i++;
	}
}

void			gpipes(t_temp *tmp, t_cmd *cmd, int j)
{
	int			*fd;
	pid_t		pid;
	int			k;
	int			s;

	if (!(fd = malloc(sizeof(int) * tmp->nb_pipes * 2)))
		general_free(tmp);
	open_dup(fd, tmp);
	k = 0;
	s = 0;
//	printf("pipes == [%d]", tmp->nb_pipes);
	while (tmp->outpipe[k])
	{
//		printftab(tmp->inpipe[k]);
//		printftab(tmp->outpipe[k]);
//		printftab(tmp->cpypipe[k]);
		if ((pid = fork()) == 0)
		{
			if (k != 0)
			{
				if (dup2(fd[s - 2], 0) < 0)
				{
					printf("1error\n");
					exit(0);
				}
			}
			if (tmp->outpipe[k + 1] != NULL)
			{
				if (dup2(fd[s + 1], 1) < 0)
				{
					printf("2error\n");
					exit(0);
				}
			}
			close_dup(fd, tmp);
			tmp->strcmd = tmp->outpipe[k];
			tmp->strcmdin = tmp->inpipe[k];
			tmp->cpytab = tmp->cpypipe[k];
			cmd ? check_redi(tmp->strcmdin, tmp) : 0;
			((tmp->flag[2] || tmp->flag[1]) && tmp->flag[2] != -1 && tmp->flag[1] != -1)
				? skip_redi(tmp, 0, 0) : 0;
			(tmp->strcmd) ? j = cmd_exist(tmp->strcmd[0], tmp, 0) : 0;
			tmp->flag[0] = (j > 0) ? 1 : 0;
			launcher_cmd(tmp->outpipe[k][0], tmp, j, 1);
			tmp->flag[1] == 1 ? close(tmp->fd) : 0;
			tmp->flag[2] == 1 ? close(tmp->fdi) : 0;
			exit(0);
		}
		else
		{
			signal(SIGINT, sighandler5);
			signal(SIGQUIT, sighandler3);
			s += 2;
			k++;
		}
	}
	close_dup(fd, tmp);
	int status;
	for (int i = 0; i < tmp->nb_pipes + 1; i++)
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
		}
	}
	signal(SIGINT, sighandler);
	free(fd);
	ft_free_triple_tab(tmp->inpipe);
	ft_free_triple_tab(tmp->outpipe);
	ft_free_triple_tab(tmp->cpypipe);
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
		if (j == -1)
		{
			(cmd != NULL) ? free_cmd(cmd) : 0;
			general_free(tmp);
		}
		if (j < 0)
		{
			(cmd != NULL) ? free_cmd(cmd) : 0;
			tmp->tabpath ? ft_free_tab(tmp->tabpath) : 0;
			break ;
		}
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
