/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principal_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:11:19 by lryst             #+#    #+#             */
/*   Updated: 2020/10/25 16:16:58 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (ft_strcmp(head->input, " "))
			i++;
		head = head->next;
	}
	return (i);
}

/*
** Fonction qui modifie strcmd avec la liste, maj + supp des espaces
*/

char			**llist_astring(t_cmd *head, char **tabstr)
{
	int			i;

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
}

void			launcher_cmd2(char *tabcmd, t_temp *tmp, int j, t_cmd *cmd)
{
	if (j == 7)
		gestion_unset(tmp);
	else if (j == 8)
		gestion_echo(cmd, tmp);
	else if (j == 9 && command_bin(tmp->strcmd, tmp) == 0)
		return ;
	else
	{
		g_ret = 127;
		ft_printf("minishell: command not found: %s\n", tabcmd);
	}	
}

void			launcher_cmd(char *tabcmd, t_temp *tmp, int j, t_cmd *cmd)
{
	if (tabcmd[0] == 0 ||  j == -2 || tmp->flag[1] == -1 || tmp->flag[2] == -1)
		return ;
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
	else
		launcher_cmd2(tabcmd, tmp, j, cmd);
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
		printf("tabcmd[%d] = [%s]\n", i, tabcmd[i]);
		initialize(tmp);
		j = 0;
		cmd = NULL;
		separator_string(&cmd, tabcmd[i], tmp);
		(cmd) ? tmp->strcmd = llist_astring(cmd, tmp->strcmd) : 0;
//aqui viene el pipe
		cmd ? check_redi(tmp->strcmd, tmp) : 0;
		((tmp->flag[2] || tmp->flag[1]) && tmp->flag[2] != -1 && tmp->flag[1] != -1)
			? skip_redi(tmp->strcmd) : 0;
		(tmp->strcmd) ? j = cmd_exist(tmp->strcmd[0], tmp) : 0;
		tmp->flag[0] = (j > 0) ? 1 : 0;
		launcher_cmd(tabcmd[i], tmp, j, cmd);
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
	free(tmp->tabcmd);
	ft_free(line);
	return (1);
}
