/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principal_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:11:19 by lryst             #+#    #+#             */
/*   Updated: 2020/11/08 16:11:12 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printftab(char **tab)// a borrar
{
	ft_printf("----printtab----\n");
	for (int i = 0; tab[i]; i++)
		ft_printf("---[%d], --- [%s]\n", i, tab[i]);
	ft_printf("-----------------\n");
}

void	printflist(t_cmd *cmd)
{
	t_cmd *tmp;

	tmp = cmd;
	ft_printf("----printlist----\n");
	while (tmp)
	{
		ft_printf("list in[%s] out[%s]\n",tmp->input, tmp->output);
		tmp = tmp->next;
	}
	ft_printf("-----------------\n");
}

/*
** fonction qui compte la liste sans les espaces de echo -n
*/

int				mlist_size(t_cmd *head)
{
	int			i;

	i = 0;
	if (!head)
		return (i);
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

/*
** Fonction qui modifie strcmd avec la liste, maj + supp des espaces
*/

void			llist_astring(t_cmd *head, t_temp *tmp)
{
	int			i;

	i = 0;
	if (head)
	{
		ft_free_double_tab(tmp->strcmd);
		tmp->strcmd = (char**)malloc(sizeof(char*) * (mlist_size(head) + 1));
		tmp->strcmdin = (char**)malloc(sizeof(char*) * (mlist_size(head) + 1));
		while (head)
		{
			tmp->strcmd[i] = ft_strdup(head->output);
			tmp->strcmdin[i++] = ft_strdup(head->input);
			head = head->next;
		}
		tmp->strcmd[i] = 0;
		tmp->strcmdin[i] = 0;
	}
	if (!cherche_echo(tmp->strcmd))
		clean_tab2d(tmp->strcmd, tmp->strcmdin);
}
/////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

/*
** Elle cherche dans le tableau de commandes, si la commande existe
** ensuite elle free la string du tableau free(tabcmd[i])
**		for (int ll= 0; tmp->strcmd[ll] ;ll++) printf("#######[%s]\n",tmp->strcmd[ll]);
*/

//	tmp->flag[1] ? close(tmp->fd) : 0;

void			initialize(t_temp *tmp)
{
	tmp->flag[1] = 0;
	tmp->flag[2] = 0;
	tmp->tabpath = NULL;
	tmp->outpipe = NULL;
	tmp->inpipe = NULL;
	tmp->strcmd = NULL;
	tmp->strcmdin = NULL;
}

void			launcher_cmd2(char *tabcmd, t_temp *tmp, int j, int key)
{
	if (j == 7)
		gestion_unset(tmp, key);
	else if (j == 8)
		gestion_echo(tmp);
	else if (j == 9 && command_bin(tmp->strcmd, tmp, key) == 0)
		return ;
	else
	{
		g_ret = 127;
		if (key == 1)
			exit(15);
		ft_printf("minishell: command not found: %s\n", tabcmd);
	}	
}

void			launcher_cmd(char *tabcmd, t_temp *tmp, int j, int key)
{
	if (tabcmd[0] == 0 ||  j == -2 || tmp->flag[1] == -1 || tmp->flag[2] == -1)
		return ;
	else if (j == 1)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	else if (j == 2)
		gestion_cd(tmp->strcmd, tmp, key);
	else if (j == 3)
		gestion_env(tmp->strcmd, tmp, key);
	else if (j == 4)
		gestion_pwd(tmp->strcmd, tmp);
	else if (j == 5)
		gestion_nani(tmp->strcmd);
	else if (j == 6)
		gestion_export(tmp, 0, key);
	else
		launcher_cmd2(tabcmd, tmp, j, key);
}

/*
**	printf("----------cmd = [%d], redi de= [%d], redi iz=[%d], fd = [%d], fdi[%d]\n", tmp->flag[0], tmp->flag[1], tmp->flag[2], tmp->fd, tmp->fdi);
**	printf("--------------j= %d \n", j);
*/


static void		gestion_line(char **tabcmd, t_temp *tmp, int i)
{
	int			j;
	t_cmd		*cmd;

	while (tabcmd[++i])
	{
	//	printf("tabcmd[%d] = [%s]\n", i, tabcmd[i]);
		initialize(tmp);
		j = 0;
		cmd = NULL;
		separator_string(&cmd, tabcmd[i], tmp); // liste chaine - tmp->strcmd
//		printftab(tmp->strcmd);
		ft_free_double_tab(tmp->strcmd);
		tmp->strcmd = NULL;
		(cmd) ? j = split3d(cmd, tmp) : 0;
		if (j < 0)
		{
			(cmd != NULL) ? free_cmd(cmd) : 0;
			tmp->tabpath ? ft_free_tab(tmp->tabpath) : 0;
//			ft_free_double_tab(tabcmd);
			break ;
		}
		if (tmp->outpipe)
		{
			int fd[2];
			pid_t pid;
			int fdd = 0;
			int k = 0;
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
						? skip_redi(tmp->strcmdin, tmp) : 0;
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
					int status;
					if ((pid = waitpid(pid, &status, WUNTRACED | WCONTINUED)) == -1)
						exit(1);
					if (WIFEXITED(status)) // toca mirar bien a que momento del tmp->outpipe[k][??] hacerlo, mirar bien las comandas que dejen poner varios comandos al mismo tiempo
					{
						if (WEXITSTATUS(status) == 15)
							ft_printf("minishell: command not found: %s\n", tmp->outpipe[k][0]);
						if (WEXITSTATUS(status) == 16)
							ft_printf("minishell: /: is a directory\n");
						if (WEXITSTATUS(status) == 17)
							ft_printf("minishell: cd: HOME not set\n");
						if (WEXITSTATUS(status) == 18)
							ft_printf("minishell: cd: %s: No such file or directory\n",tmp->outpipe[k][1]);
						if (WEXITSTATUS(status) == 19)
							ft_printf("env: %s: No such file or directory\n", tmp->outpipe[k][1]);
						if (WEXITSTATUS(status) == 20)
							ft_printf("minishell: export: `%s': not a valid identifier\n", tmp->outpipe[k][1]);
						if (WEXITSTATUS(status) == 22)
							ft_printf("minishell: unset: `%s': not a valid identifier \n",
								tmp->outpipe[k][1]);
						if (WEXITSTATUS(status) == 23)
							ft_printf("minishell: syntax error near unexpected token `%s'\n", tmp->outpipe[k][1]);
						if (WEXITSTATUS(status) == 24)
							ft_printf("minishell: syntax error near unexpected token `newline'\n");
						if (WEXITSTATUS(status) == 13)
							ft_printf("minishell: %s: Permission denied\n", tmp->outpipe[k][0]);
						if (WEXITSTATUS(status) == 2)
							ft_printf("minishell: %s: No such file or directory\n", tmp->outpipe[k][0]);
					}
					wait(NULL);
					close(fd[1]);
					fdd = fd[0];
					k++;
				}
			}
			ft_free_triple_tab(tmp->inpipe);
			ft_free_triple_tab(tmp->outpipe);
		}
		else
		{
			(cmd) ? llist_astring(cmd, tmp) : 0;
			printftab(tmp->strcmd);
			printftab(tmp->strcmdin);
			cmd ? check_redi(tmp->strcmdin, tmp, 0) : 0;
			((tmp->flag[2] || tmp->flag[1]) && tmp->flag[2] != -1 && tmp->flag[1] != -1)
				? skip_redi(tmp->strcmdin, tmp) : 0;
			(tmp->strcmd) ? j = cmd_exist(tmp->strcmd[0], tmp) : 0;
			tmp->flag[0] = (j > 0) ? 1 : 0;
			launcher_cmd(tabcmd[i], tmp, j, 0);
			ft_free_double_tab(tmp->strcmd);
			ft_free_double_tab(tmp->strcmdin);
			tmp->flag[1] == 1 ? close(tmp->fd) : 0;
			tmp->flag[2] == 1 ? close(tmp->fdi) : 0;
		}
		(cmd != NULL) ? free_cmd(cmd) : 0;
//		ft_free(tabcmd[i]);
		tmp->tabpath ? ft_free_tab(tmp->tabpath) : 0;
	
	}
}

/*
** ft_getline reçoit avec l'aide du get_next_line la ligne avec les commandes...
** ...et lance aussi le parsing
*/

int				ft_getline(t_temp *tmp)
{
	char		*line;
	int			ret;

	line = NULL;
	if ((ret = ft_gnl(0, &line)) == -1
		|| (tmp->tabcmd = ft_split_line(line)) == NULL)
		general_free(tmp);
	if (ret == 0)
		return (0);
	if (tmp->tabcmd != NULL && tmp->tabcmd[0])
		gestion_line(tmp->tabcmd, tmp, -1);
//	free(tmp->tabcmd);
	ft_free_double_tab(tmp->tabcmd);
	ft_free(line);
	return (1);
}
