/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principal_parcing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 02:30:51 by corozco           #+#    #+#             */
/*   Updated: 2020/09/27 14:37:28 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int			mlist_size(l_cmd *head)
{
	int		i;

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
*/
/*
** Elle cherche dans le tableau de commandes, si la commande existe
** ensuite elle free la string du tableau free(tabcmd[i])
*/

static void		gestion_line(char **tabcmd, t_temp *tmp)
{
	int i;
	l_cmd	*cmd;

	i = -1;
	while (tabcmd[++i])
	{
		cmd = NULL;
		separator_string(&cmd, tabcmd[i], tmp);

//		ft_printf("list size = %d \n", mlist_size(cmd));
//		exit(1);
		if (tabcmd[i][0] == 0)
			;
		else if (ft_strcmp(tabcmd[i], "exit") == 0)
		{
			write(1, "exit\n", 5);
			exit(0);
		}
		else if (ft_strcmp(tmp->strcmd[0], "cd") == 0)
			gestion_cd(tabcmd[i], tmp);
		else if (ft_strcmp(tmp->strcmd[0], "env") == 0)
			gestion_env(tmp);
		else if (ft_strcmp(tmp->strcmd[0], "pwd") == 0)
			gestion_pwd(tabcmd, tmp, i);
		else if (ft_strcmp(tmp->strcmd[0], "nani") == 0)
			gestion_nani(tmp->strcmd);
		else if (ft_strcmp(tmp->strcmd[0], "export") == 0)
			gestion_export(tmp, 0);
		else if (ft_strcmp(tmp->strcmd[0], "unset") == 0)
			gestion_unset(tmp);
		else if (ft_strcmp(tmp->strcmd[0], "echo") == 0)
			gestion_echo(cmd);
		else if (command_bin(tmp->strcmd, tmp) == 0)
			;
		else
		{
			g_ret = 127;
			ft_printf("minishell: command not found: %s\n", tabcmd[i]);
		}
		free_tmps(tabcmd, i, tmp);
		if (cmd != NULL)
			free_cmd(cmd);
	}
}

/*
** ft_getline reçoit avec l'aide du get_next_line la ligne avec les commandes...
** ...et lance aussi le parcing
*/

void			ft_getline(t_temp *tmp)
{
	char		*line; // meter este line en la structura

	line = NULL;
	if (ft_gnl(0, &line) == -1 || (tmp->tabcmd = ft_split_line(line)) == NULL)
		general_free(tmp);
	if (tmp->tabcmd != NULL && tmp->tabcmd[0])
	{

		printf("line = [%s]\n", line);
		gestion_line(tmp->tabcmd, tmp);
//ft_free_double_tab(tmp->tabcmd);
	}
	free(tmp->tabcmd);
	free(line);
}
