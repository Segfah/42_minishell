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

void			gestion_missing(t_temp *tmp, int key)
{
	int			i;

	i = -1;
	while (tmp->strcmd[++i])
	{
		if (!ft_strcmp("]", tmp->strcmd[i]))
			return ;
	}
	if (key == 1)
		exit(21);
	ft_printf("minishell: [: missing `]'\n");
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
		gestion_missing(tmp, key);
	else if (j == 7)
		gestion_unset(tmp);
	else if (j == 8)
		gestion_echo(tmp, key);
	else if (j == 9 && command_bin(tmp->strcmd, tmp, key) == 0)
		return ;
	else if (j == 11)
		point_filename(tmp->strcmd);
	else
	{
		g_ret = 127;
		if (key == 1)
			exit(28);
		echo_join(tmp->cpytab, tmp->strcmd);
	}
	(void)tabcmd;
}

void			exit_join(char **tabin, char **tabout)
{
	int i;
	int j;

	i = 1;
	j = 2;
	
	//key ? ft_nb_exit(46) : 0;
	write(1, "exit\n", 5);
	write(2, "minishell: exit: ", 17);
	while (tabin[j] && tabout[i] && ft_strcmp(tabin[j], " "))
	{
		write(2, tabout[i], ft_strlen(tabout[i]));
		j++;
		i++;
	}
	write(2, ": numeric argument required\n", 28);
	
}

int	ft_intlen(int n)
{
	int		len;

	if (n == 2147482647)
		return (11);
	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void			exit_arg(char **strcmd, int key)
{
	if (strcmd[2])
	{
		g_ret = 1;
		if (!key)
			write(1, "exit\n", 5);
		key ? ft_nb_exit(45) : 0;
		write(2, "minishell: exit: too many arguments\n", 36);
	}
	else
	{
		g_ret = ft_atoi((const char*)strcmd[1]);
		write(1, "exit\n", 5);
		exit(g_ret);
	}
}

void			gestion_exit(char **strcmd, t_temp *tmp, int key)
{
	if (!strcmd[1] && !key)
	{
		g_ret = 0;
		write(1, "exit\n", 5);
		exit (g_ret);
	}
	else
	{
		if (ft_intlen(ft_atoi(strcmd[1])) == (int)ft_strlen(strcmd[1]) &&
		(tmp->cpytab[3] == NULL || !ft_strcmp(tmp->cpytab[3], " ")))
		{ 
			key ? ft_nb_exit(45) : 0;
			exit_arg(strcmd, key);
		}
		else
		{
			g_ret = 255;
			exit_join(tmp->cpytab, tmp->strcmd);
			exit(g_ret);
		}
	}
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

int				check_export(char *src, char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (check_env(str[i], 1) == -1)
		{
			ft_printf("minishell: %s: `%s': not a valid identifier\n"
				, src, str[i]);
		}
		i++;
	}
	return (0);
}

void			print_error_redi(char *str, int key)
{
	if (key == -1)
		ft_printf("minishell: syntax error near unexpected token `>'\n");
	if (key == -2)
		ft_printf("minishell: syntax error near unexpected token `>>'\n");
	if (key == -3)
		ft_printf("minishell: syntax error near unexpected token `<'\n");
	if (key == -4)
		ft_printf("minishell: syntax error near unexpected token `%s'\n", str);
	if (key == -5)
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
}

int				error_line2(t_cmd *cmd, t_temp *tmp)
{
	int			ret;

	ret = (cmd) ? llist_astring(cmd, tmp) : 0;
	if (ret == -1)
		exit(1);
	if (tmp->strcmdin && (ret = check_redi_2(tmp->strcmdin, 1)) < 0)
	{
		print_error_redi(tmp->strcmd[check_redi_2(tmp->strcmd, 0) + 1], ret);
		ft_free_double_tab(tmp->strcmd);
		ft_free_double_tab(tmp->strcmdin);
		ft_free_double_tab(tmp->cpytab);
		(cmd != NULL) ? free_cmd(cmd) : 0;
		return (-1);
	}
	return (0);
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
			ft_free_double_tab(tmp->strcmd);
			(cmd != NULL) ? free_cmd(cmd) : 0;
			print_error(ret);
			return (-1);
		}
		if (error_line2(cmd, tmp) == -1)
			return (-1);
		ft_free_double_tab(tmp->strcmd);
		ft_free_double_tab(tmp->strcmdin);
		ft_free_double_tab(tmp->cpytab);
		(cmd != NULL) ? free_cmd(cmd) : 0;
	}
	return (0);
}

void			pparent_errors(int status, t_temp *tmp, int *k)
{
	if (WEXITSTATUS(status) == 15)
		ft_printf("minishell: command not found: %s\n", tmp->outpipe[*k][0]);
	if (WEXITSTATUS(status) == 16)
		ft_printf("minishell: /: is a directory\n");
//	if (WEXITSTATUS(status) == 17)
//		ft_printf("minishell: cd: HOME not set\n");
//	if (WEXITSTATUS(status) == 18)
//		ft_printf("minishell: cd: %s: No such file or directory\n"
//		, tmp->outpipe[*k][1]);
//	if (WEXITSTATUS(status) == 19)
//		ft_printf("env: %s: No such file or directory\n", tmp->outpipe[*k][1]);
//	if (WEXITSTATUS(status) == 20)
//		check_export("export", tmp->outpipe[*k]);
	if (WEXITSTATUS(status) == 21)
		ft_printf("minishell: [: missing `]'\n");
//	if (WEXITSTATUS(status) == 22)
//		check_export("unset", tmp->outpipe[*k]);
	if (WEXITSTATUS(status) == 23)
		ft_printf("minishell: syntax error near unexpected token `%s'\n"
		, tmp->outpipe[*k][check_redi_2(tmp->outpipe[*k], 0) + 1]);
	if (WEXITSTATUS(status) == 24)
		ft_printf("minishell: syntax error near unexpected token `newline'\n");
	//if (WEXITSTATUS(status) == 28)
		//echo_join(tmp->inpipe[*k], tmp->outpipe[*k]);
}

void			pparent(pid_t pid, t_temp *tmp, int *k)
{
	int status;

	if ((pid = waitpid(pid, &status, WUNTRACED | WCONTINUED)) == -1)
		exit(1);
	if (WIFEXITED(status))
	{
		pparent_errors(status, tmp, k);
		//if (WEXITSTATUS(status) == 26)
		//{
		//	write(2, "minishell: .: filename argument required\n", 41);
		//	write(2, ".: usage: . filename [arguments]\n", 33);
		//
//		if (WEXITSTATUS(status) == 25)
//			ft_printf("minishell: %s: Is a directory\n"
//			, tmp->outpipe[*k][check_redi_2(tmp->outpipe[*k], 0) + 1]);
//		if (WEXITSTATUS(status) == 27)
//			ft_printf("minishell: %s:  No such file or directory\n"
//			, tmp->outpipe[*k][check_redi_2(tmp->outpipe[*k], 0) + 1]);
		if (WEXITSTATUS(status) == 13)
			ft_printf("minishell: %s: Permission denied\n"
			, tmp->outpipe[*k][0]);
		if (WEXITSTATUS(status) == 2)
			ft_printf("minishell: %s: No such file or directory\n"
			, tmp->outpipe[*k][0]);
		if (WEXITSTATUS(status) == 45)
			write(2, "minishell: exit: too many arguments\n", 36);
		if (WEXITSTATUS(status) == 46)
			;
	}
	(*k)++;
}

void			gpipes(t_temp *tmp, t_cmd *cmd, int j)
{
	int			fd[2];
	pid_t		pid;
	int			fdd;
	int			k;

	fdd = 0;
	k = 0;
	while (tmp->outpipe[k])
	{
		pipe(fd);
		if ((pid = fork()) == 0)
		{
			dup2(fdd, 0);
			if (tmp->outpipe[k + 1] != NULL)
				dup2(fd[1], 1);
			close(fd[0]);
			tmp->strcmd = tmp->outpipe[k];
			tmp->strcmdin = tmp->inpipe[k];
			cmd ? check_redi(tmp->strcmdin, tmp, 1) : 0;
			((tmp->flag[2] || tmp->flag[1]) && tmp->flag[2] != -1 && tmp->flag[1] != -1)
				? skip_redi(tmp, 0) : 0;
			(tmp->strcmd) ? j = cmd_exist(tmp->strcmd[0], tmp) : 0;
			tmp->flag[0] = (j > 0) ? 1 : 0;
			launcher_cmd(tmp->outpipe[k][0], tmp, j, 1);
			(cmd != NULL) ? free_cmd(cmd) : 0;
			tmp->tabpath ? ft_free_tab(tmp->tabpath) : 0;
			tmp->flag[1] == 1 ? close(tmp->fd) : 0;
			tmp->flag[2] == 1 ? close(tmp->fdi) : 0;
			exit(1);
		}
		else
		{
			pparent(pid, tmp, &k);
			close(fd[1]);
			fdd = fd[0];
		}
	}
	ft_free_triple_tab(tmp->inpipe);
	ft_free_triple_tab(tmp->outpipe);
}

void			npipe(char **tabcmd, t_temp *tmp, t_cmd *cmd, int i)
{
	int ret;
	int j;

	j = 0;
	ret = (cmd) ? llist_astring(cmd, tmp) : 0;
	if (ret == -1)
		exit(1);
	cmd ? check_redi(tmp->strcmdin, tmp, 0) : 0;
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
			exit(1);
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
//	general_free(tmp);
/*
**	1) il faut regarder ft_split_line
**	2) enlever le int de ft_getline ça ne sert à rien
*/
		if (ret == 0)
			return (0);
		if (tmp->tabcmd != NULL && tmp->tabcmd[0])
			gestion_line(tmp->tabcmd, tmp, -1);
		ft_free_double_tab(tmp->tabcmd);
		ft_free(line);
	}
	return (1);
}
