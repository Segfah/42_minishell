/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principal_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:11:19 by lryst             #+#    #+#             */
/*   Updated: 2020/10/21 19:32:25 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static char		**build_cmd(t_temp *tmp, char *cmd)
{
	int			a;
	char		*path;
	char		**tabpath;
	char		*temp;

	a = -1;
	if (search_env("PATH", tmp, 0, &path) == -1)
		return (NULL);
	if (!(tabpath = ft_split(path, ':')))
		return (NULL);
	while (tabpath[++a] != NULL)
	{
		temp = tabpath[a];
		if (!(tabpath[a] = ft_strjoin(tabpath[a], "/")))
			return (NULL);
		ft_free(temp);
		temp = tabpath[a];
		if (!(tabpath[a] = ft_strjoin(tabpath[a], cmd)))
			return (NULL);
		ft_free(temp);
	}
	ft_free(path);
	return (tabpath);
}

static int		cmd_is_here(char **path)
{
	int			i;
	struct stat	stats;

	i = -1;
	while (path[++i])
	{
		if (stat(path[i], &stats) == 0)
			return (i);
	}
	return (-1);
}

/*
** si algo falla, era
**	if (flag)
**		return (flag);
**	if (!flag && !search_env("PATH", tmp, 1, NULL))
**		return (flag);
** y
**	if ((tmp->status = cmd_is_here(tmp->tabpath)) == -1)
** si el flag deja de servir cambiar el !(flag = 0) por un flag = 0
** despues del return (-2);
*/

int			cmd_exist(char *cmd, t_temp *tmp)
{
	int		flag;

	if (!(flag = 0) && !cmd)
		return (-2);
	flag = !ft_strcmp(cmd, "exit") ? 1 : flag;
	flag = !ft_strcmp(cmd, "cd") ? 2 : flag;
	flag = !ft_strcmp(cmd, "env") ? 3 : flag;
	flag = !ft_strcmp(cmd, "pwd") ? 4 : flag;
	flag = !ft_strcmp(cmd, "nani") ? 5 : flag;
	flag = !ft_strcmp(cmd, "export") ? 6 : flag;
	flag = !ft_strcmp(cmd, "unset") ? 7 : flag;
	flag = !ft_strcmp(cmd, "echo") ? 8 : flag;
	if (!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1))
		flag = 9;
	if (flag || (!flag && !search_env("PATH", tmp, 1, NULL)))
		return (flag);
	if (!(tmp->tabpath = build_cmd(tmp, cmd)))
		return (-1);
	if ((tmp->status = cmd_is_here(tmp->tabpath)) == -1 || tmp->status == 0)
	{
		//ft_free_tab(tmp->tabpath);
		return (0);
	}
	return (9);
}

/*
** fonction qui compte la liste sans les espaces de echo -n
*/

int			mlist_size(t_cmd *head)
{
	int		i;

	i = 0;
	if (!head)
		return (i);
	while (head)
	{
		if (ft_strcmp(head->input, " "))
			i++;
		head = head->next;
	}
	return (i);
}

/*
** Fonction qui modifie strcmd avec la liste, maj + supp des espaces
*/

char		**llist_astring(t_cmd *head, char **tabstr)
{
	int		i;

	i = 0;
	if (head)
	{
		ft_free_double_tab(tabstr);
		if (!(tabstr = (char**)malloc(sizeof(char*) * (mlist_size(head) + 1))))
			return (NULL);
		while (head)
		{
			if (ft_strcmp(head->input, " "))
				tabstr[i++] = ft_strdup(head->output);
			head = head->next;
		}
		tabstr[i] = 0;
	}
	return (tabstr);
}
/////////////////////////////////////////////////////////////////////////
int			is_redi(char *str)
{
	return (!(ft_strcmp(">", str)) || !(ft_strcmp(">>", str))
			|| !(ft_strcmp("<", str)));
}

int			simple_redi(char *path, t_temp *tmp)
{
	(tmp->fd > 0) ? close(tmp->fd) : 0;
	tmp->fd = 0;
	if ((tmp->fd = open(path, O_RDWR | O_TRUNC |
			O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		printf("minishell: %s: %s\n", strerror(errno), path);
		return (-1);
	}
	return (0);
}


int		double_redi(char *path, t_temp *tmp)
{
	(tmp->fd > 0) ? close(tmp->fd) : 0;
	tmp->fd = 0;
	if ((tmp->fd = open(path, O_APPEND | O_WRONLY | O_CREAT, 0644)) == -1)
	{
		ft_printf("minishell: %s: %s\n", strerror(errno), path);
		return (-1);
	}
	return (0);
}

int			contre_redi(char *path, t_temp *tmp)
{
	(tmp->fdi > 0) ? close(tmp->fdi) : 0;
	tmp->fdi = 0;
	if ((tmp->fdi = open(path, O_RDONLY)) == -1)
	{
		printf("minishell: %s: %s\n", strerror(errno), path);
		return (-1);
	}
	return (0);
}

int		check_redi(char **cmd, t_temp *tmp)
{
	int		i;

	tmp->fd = 0;
	tmp->fdi = 0;
	i = -1;
	while (cmd[++i]) //Posiblemente cambie este por uno que haga el check de la lista encadenada, y que mire el input y no el otro
	{
		if (is_redi(cmd[i]))
		{
			if (cmd[i + 1])
			{
				if (is_redi(cmd[i + 1]))
				{
					printf("minishell: syntax error near unexpected token `%s'\n", cmd[i]);
					return (tmp->flag[1] = -1);
				}
			}
			else
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				return (tmp->flag[1] = -1);
			}
		}
	}
	i = -1;
	while (cmd[++i])
	{
//		if (!(ft_strcmp(">", cmd[i]))) // y que en la lista encadenada no sea ">" con guimes
		if (!(ft_strcmp(">", cmd[i])))
		{
			tmp->flag[1] = 1;
			if (tmp->flag[2] != -1 && simple_redi(cmd[i + 1], tmp) == -1)
				return (tmp->flag[1] = -1);
		}
		else if (tmp->flag[2] != -1 && !(ft_strcmp(">>", cmd[i])))
		{
			tmp->flag[1] = 1;
			if (double_redi(cmd[i + 1], tmp) == -1)
				return (tmp->flag[1] = -1);
		}
		else if (!(ft_strcmp("<", cmd[i])))
		{
			tmp->flag[2] = 1;
			if (contre_redi(cmd[i + 1], tmp) == -1)
				return (tmp->flag[2] = -1);
		}
	}
	return (0);
}

void		skip_redi(char **cmd)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (!(ft_strcmp(">", cmd[i])) || !(ft_strcmp(">>", cmd[i])) || !(ft_strcmp("<", cmd[i])))
		{
			ft_free(cmd[i]);
			ft_free(cmd[i + 1]);
			i = i + 2;
		}
		else
			cmd[j++] = cmd[i++];
	}
	cmd[j] = 0;
}

//////////////////////////////////////////////////////////////////////////

/*
** Elle cherche dans le tableau de commandes, si la commande existe
** ensuite elle free la string du tableau free(tabcmd[i])
**		for (int ll= 0; tmp->strcmd[ll] ;ll++) printf("#######[%s]\n",tmp->strcmd[ll]);
*/

//	tmp->flag[1] ? close(tmp->fd) : 0;

static void		gestion_line(char **tabcmd, t_temp *tmp)
{
	int i;
	int j;
	t_cmd	*cmd;

	i = -1;
	while (tabcmd[++i])
	{
		tmp->flag[1] = 0;
		tmp->flag[2] = 0;
		tmp->tabpath = NULL;
		j = 0;
		cmd = NULL;
		separator_string(&cmd, tabcmd[i], tmp);
		(cmd) ? tmp->strcmd = llist_astring(cmd, tmp->strcmd) : 0;
//aqui viene el pipe
		cmd ? check_redi(tmp->strcmd, tmp) : 0;
		((tmp->flag[2] || tmp->flag[1]) && tmp->flag[2] != -1 && tmp->flag[1] != -1) ? skip_redi(tmp->strcmd) : 0;
		(tmp->strcmd) ? j = cmd_exist(tmp->strcmd[0], tmp) : 0;

		printf("----------cmd = [%d], redi de= [%d], redi iz=[%d], fd = [%d], fdi[%d]\n", tmp->flag[0], tmp->flag[1], tmp->flag[2], tmp->fd, tmp->fdi);
		printf("--------------j= %d \n", j);
		tmp->flag[0] = (j > 0) ? 1 : 0;
		if (tabcmd[i][0] == 0 ||  j == -2 || tmp->flag[1] == -1 || tmp->flag[2] == -1)
			;
		else if (j == 1)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
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
		else if (j == 7)
			gestion_unset(tmp);
		else if (j == 8)
			gestion_echo(cmd, tmp);
		else if (j == 9 && command_bin(tmp->strcmd, tmp) == 0)
			;
		else
		{
			g_ret = 127;
			ft_printf("minishell: command not found: %s\n", tabcmd[i]);
		}
		ft_free_double_tab(tmp->strcmd);
		if (cmd != NULL)
			free_cmd(cmd);
		ft_free(tabcmd[i]);
		tmp->tabpath ? ft_free_tab(tmp->tabpath) : 0;
		tmp->flag[1] == 1 ? close(tmp->fd) : 0;
		tmp->flag[2] == 1 ? close(tmp->fdi) : 0;
	}
}

/*
** ft_getline reçoit avec l'aide du get_next_line la ligne avec les commandes...
** ...et lance aussi le parsing
*/

int			ft_getline(t_temp *tmp)
{
	char		*line; // meter este line en la structura
	int			ret;

	line = NULL;
	if ((ret = ft_gnl(0, &line)) == -1 || (tmp->tabcmd = ft_split_line(line)) == NULL)
		general_free(tmp);
	if (ret == 0)
		return (0);
	if (tmp->tabcmd != NULL && tmp->tabcmd[0])
		gestion_line(tmp->tabcmd, tmp);
//		ft_free_double_tab(tmp->tabcmd);
	free(tmp->tabcmd);
	ft_free(line);
	return (1);
}