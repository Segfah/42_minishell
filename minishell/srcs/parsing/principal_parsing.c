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
	int i;

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
	t_cmd *tmp;

	tmp = cmd;
	ft_printf("----printlist----\n");
	while (tmp)
	{
		ft_printf("list in[%s] out[%s]\n", tmp->input, tmp->output);
		tmp = tmp->next;
	}
	ft_printf("-----------------\n");
}

void			gestion_missing(t_temp *tmp)
{
	int			i;

	i = -1;
	while (tmp->strcmd[++i])
	{
		if (!ft_strcmp("]", tmp->strcmd[i]))
			return ;
	}
	ft_fprintf(2 ,"minishell: [: missing `]'\n");
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

void			launcher_cmd2(char *tabcmd, t_temp *tmp, int j, int key)
{
	if (j == 10)
		gestion_missing(tmp);
	else if (j == 7)
		gestion_unset(tmp);
	else if (j == 8)
		gestion_echo(tmp);
	else if (j == 9 && command_bin(tmp->strcmd, tmp) == 0)
		return ;
	else if (j == 11)
		point_filename(tmp->strcmd);
	else
		cmd_not_found(tabcmd, tmp);
	(void)key;
	(void)tabcmd;
}



void			launcher_cmd(char *tabcmd, t_temp *tmp, int j, int key)
{
	if (tabcmd[0] == 0 || j == -2 || tmp->flag[1] == -1 || tmp->flag[2] == -1)
		return ;
	else if (j == 1)
		gestion_exit(tmp->strcmd, tmp, key);
	else if (j == 2)
		gestion_cd(tmp->strcmd, tmp);
	else if (j == 3)
		gestion_env(tmp->strcmd, tmp);
	else if (j == 4)
		gestion_pwd(tmp->strcmd, tmp);
	else if (j == 5)
		gestion_nani(tmp->strcmd);
	else if (j == 6)
		gestion_export(tmp, 0);
	else
		launcher_cmd2(tabcmd, tmp, j, key);
}

void			print_error_redi(char *str, int key)
{
	if (key == -1)
		ft_fprintf(2, "minishell: syntax error near unexpected token `>'\n");
	if (key == -2)
		ft_fprintf(2, "minishell: syntax error near unexpected token `>>'\n");
	if (key == -3)
		ft_fprintf(2, "minishell: syntax error near unexpected token `<'\n");
	if (key == -4)
		ft_fprintf(2, "minishell: syntax error near unexpected token `%s'\n", str);
	if (key == -5)
		ft_fprintf(2, "minishell: syntax error near unexpected token `newline'\n");
	if (key == -35)
		ft_fprintf(2, "minishell: syntax error near unexpected token `|'\n");
}

int				error_line2(t_cmd *cmd, t_temp *tmp)
{
	int			ret;

	ret = (cmd) ? llist_astring(cmd, tmp) : 0;
	if (ret == -1)
	{
		free_cmd(cmd);
		general_free(tmp);
	}
	if (tmp->strcmdin && (ret = check_redi_2(tmp->strcmdin, 1)) < 0)
	{
		print_error_redi(tmp->strcmd[check_redi_2(tmp->strcmd, 0) + 1], ret);
		ft_free_double_tab(tmp->strcmd);
		ft_free_double_tab(tmp->strcmdin);
		ft_free_double_tab(tmp->cpytab);
		(cmd != NULL) ? free_cmd(cmd) : 0;
		g_ret = 258;
		return (-1);
	}
	return (0);
}

int			error_multi(t_cmd *cmd, t_temp *tmp)
{
	ft_fprintf(2, "error multi\n");
	ft_free_double_tab(tmp->strcmd);
	ft_free_double_tab(tmp->strcmdin);
	ft_free_double_tab(tmp->cpytab);
	(cmd != NULL) ? free_cmd(cmd) : 0;
	g_ret = 258;
	return (-1);
}

int				error_line(char **tabcmd, t_temp *tmp, int i)
{
	t_cmd		*cmd;
	int			ret;

	while (tabcmd[++i])
	{
		initialize(tmp, &ret);
		cmd = NULL;
		separator_string(&cmd, tabcmd[i], tmp);
		if ((ret = len_split3d(cmd)) < 0)
		{
			if (ret != -3 && (g_ret = 258))
			{
				ft_free_double_tab(tmp->strcmd);
				(cmd != NULL) ? free_cmd(cmd) : 0;
				print_error(ret);
				g_ret = 258;
				return (-1);
			}
		}
		if (error_line2(cmd, tmp) == -1)
			return (-1);
		if (ret == -3)
			return (error_multi(cmd, tmp));
		ft_free_double_tab(tmp->strcmd);
		ft_free_double_tab(tmp->strcmdin);
		ft_free_double_tab(tmp->cpytab);
		(cmd != NULL) ? free_cmd(cmd) : 0;
	}
	return (0);
}

void			pparent(pid_t pid, t_temp *tmp, int *k)
{
	int status;

	if ((pid = waitpid(pid, &status, WUNTRACED | WCONTINUED)) == -1)
		general_free(tmp);
	if (WIFEXITED(status))
	{
		/*
		if (WEXITSTATUS(status) == 25)
			ft_printf("minishell: %s: Is a directory\n"
			, tmp->outpipe[*k][check_redi_2(tmp->outpipe[*k], 0) + 1]);
		*/
	}
	(*k)++;
	(void)tmp;
}

void			gpipes(t_temp *tmp, t_cmd *cmd, int j)
{
	int			fd[tmp->nb_pipes * 2];
	pid_t		pid;
	int			k;
	int			s;

	for(int i = 0; i < tmp->nb_pipes; i++)
	{
		if( pipe(fd + i * 2) < 0 )
		{
			printf("3error\n");
			exit(0);
		}
	}
	k = 0;
	s = 0;
//	printf("pipes == [%d]", tmp->nb_pipes);
	while (tmp->outpipe[k])
	{
//		printftab(tmp->inpipe[k]);
//		printftab(tmp->outpipe[k]);
//		printftab(tmp->cpypipe[k]);
		
//		pipe(fd);
		if ((pid = fork()) == 0)
		{
			if (k != 0)
			{
				if ( dup2(fd[s - 2], 0) < 0)
				{
					printf("1error\n");
					exit(0);
				}
			}
			if (tmp->outpipe[k + 1] != NULL)
			{
				if( dup2(fd[s + 1], 1) < 0 )
				{
					printf("2error\n");
					exit(0);
				}
			}
			for(int i = 0; i < tmp->nb_pipes * 2; i++)
			{
				close(fd[i]);
			}
			tmp->strcmd = tmp->outpipe[k];
			tmp->strcmdin = tmp->inpipe[k];
			tmp->cpytab = tmp->cpypipe[k];
			cmd ? check_redi(tmp->strcmdin, tmp) : 0;
			((tmp->flag[2] || tmp->flag[1]) && tmp->flag[2] != -1 && tmp->flag[1] != -1)
				? skip_redi(tmp, 0) : 0;
			(tmp->strcmd) ? j = cmd_exist(tmp->strcmd[0], tmp) : 0;
			tmp->flag[0] = (j > 0) ? 1 : 0;
			launcher_cmd(tmp->outpipe[k][0], tmp, j, 1);
			tmp->flag[1] == 1 ? close(tmp->fd) : 0;
			tmp->flag[2] == 1 ? close(tmp->fdi) : 0;
			exit(0);
		}
		else
		{
//			pparent(pid, tmp, &k);
			s += 2;
			k++;
		}
	}
	for (int i = 0; i < 2 * tmp->nb_pipes; i++ )
		close( fd[i] );
	int status;
	k =0;
	for(int i = 0; i < tmp->nb_pipes + 1; i++)
	{
		status = 0;
	//	pid = waitpid(pid, &status, WUNTRACED | WCONTINUED);
		wait(&status);
		if (WIFEXITED(status))
			if (WEXITSTATUS(status) == 1)
				general_free(tmp);
		k++;
	}
	ft_free_triple_tab(tmp->inpipe);
	ft_free_triple_tab(tmp->outpipe);
	ft_free_triple_tab(tmp->cpypipe);
}

void			npipe(char **tabcmd, t_temp *tmp, t_cmd *cmd, int i)
{
	int ret;
	int j;

	j = 0;
	ret = (cmd) ? llist_astring(cmd, tmp) : 0;
	if (ret == -1)
	{
		cmd ? check_redi(tmp->strcmdin, tmp) : 0;
		general_free(tmp);
	}
	cmd ? check_redi(tmp->strcmdin, tmp) : 0;
	((tmp->flag[2] || tmp->flag[1]) && tmp->flag[2] != -1 && tmp->flag[1] != -1)
		? skip_redi(tmp, 0) : 0;
	(tmp->strcmd) ? j = cmd_exist(tmp->strcmd[0], tmp) : 0;
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
