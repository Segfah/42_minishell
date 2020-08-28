/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principal_parcing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 02:30:51 by corozco           #+#    #+#             */
/*   Updated: 2020/08/28 03:59:40 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** fonction qui va creer le nouveau tableau a partir de tabcmd (strig)
*/

void			separator_string(char *str, t_temp *tmp)
{
	tmp->strcmd = ft_split_strcmd(str, ' ');
}

/*
**	free le nouveau tableau de string (ls -la)
** [1] ls
** [2] -la
*/

void			free_tmps(char **tabcmd, int i, t_temp *tmp)
{
	int			a;

	a = 0;
	while (tmp->strcmd[a])
	{
		free(tmp->strcmd[a]);
		tmp->strcmd[a++] = NULL;
	}
	free(tmp->strcmd);
	tmp->strcmd = NULL;
	free(tabcmd[i]);
	tabcmd[i] = NULL;
}

void			gestion_nani(char **tab)
{
	int i;
	
	i = 0;
	while (tab[i] != NULL)
	{
		ft_printf("tab = [%s]\n", tab[i]);
		i++;
	}
}

/*
** Elle cherche dans le tableau de commandes, si la commande existe
** ensuite elle free la string du tableau free(tabcmd[i])
*/

static void		gestion_line(char **tabcmd, t_temp *tmp)
{
	int i;

	i = -1;
	while (tabcmd[++i])
	{
		clean_str(tabcmd[i]);
		separator_string(tabcmd[i], tmp);
		if (ft_strcmp(tabcmd[i], "exit") == 0)
			exit(0);
		else if (ft_strncmp(tabcmd[i], "cd", 2) == 0)
			gestion_cd(tabcmd[i]);
		else if (ft_strcmp(tabcmd[i], "env") == 0)
			gestion_env(tmp);
		else if (ft_strcmp(tabcmd[i], "pwd") == 0)
			gestion_pwd(tabcmd, tmp, i);
		else if (ft_strncmp(tabcmd[i], "nani", 4) == 0)
			gestion_nani(tmp->strcmd);
		else if (ft_strcmp(tmp->strcmd[0], "export") == 0)
			gestion_export(tmp, 0);
		else if (ft_strcmp(tmp->strcmd[0], "unset") == 0)
			gestion_unset(tmp);
//		else if (ft_strcmp(tmp->strcmd[0], "echo") == 0)
//			gestion_echo(tabcmd[i]);
		else if (command_bin(tmp->strcmd, tmp) == 0)
			;
		else if (tabcmd[i][0] == '\0')
			;
		else
			ft_printf("minishell: command not found: %s\n", tabcmd[i]);
		free_tmps(tabcmd, i, tmp);
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
	if (ft_gnl(0, &line) == -1 || (tmp->tabcmd = ft_split(line, ';')) == NULL)
		general_free(tmp);
	gestion_line(tmp->tabcmd, tmp);
	free(tmp->tabcmd);
	tmp->tabcmd = NULL;
	free(line);
}
