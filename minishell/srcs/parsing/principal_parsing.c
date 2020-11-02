/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principal_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:11:19 by lryst             #+#    #+#             */
/*   Updated: 2020/11/02 13:19:56 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printftab(char **tab)// a borrar
{
	printf("----printtab----\n");
	for (int i = 0; tab[i]; i++)
		printf("---[%d], --- [%s]\n", i, tab[i]);
	printf("-----------------\n");
}

void	printflist(t_cmd *cmd)
{
	t_cmd *tmp;

	tmp = cmd;
	printf("----printlist----\n");
	while (tmp)
	{
		printf("list in[%s] out[%s]\n",tmp->input, tmp->output);
		tmp = tmp->next;
	}
	printf("-----------------\n");
}

/*
** fonction qui compte la liste sans les espaces de echo -n
*/

int				mlist_size(t_cmd *head, int key)
{
	int			i;

	i = 0;
	if (!head)
		return (i);
	while (head)
	{
		if (key)
		{
			if (ft_strcmp(head->input, " "))
				i++;
		}
		else
			i++;
		head = head->next;
	}
	return (i);
}

/*
** Fonction qui modifie strcmd avec la liste, maj + supp des espaces
*/

char			**llist_astring(t_cmd *head, char **tabstr, int key)
{
	int			i;

	i = 0;
	if (head)
	{
		ft_free_double_tab(tabstr);
		if (!(tabstr = (char**)malloc(sizeof(char*) * (mlist_size(head, key) + 1))))
			return (NULL);
		while (head)
		{
			if (key)
			{
				if (ft_strcmp(head->input, " "))
				tabstr[i++] = ft_strdup(head->output);
			}
			else
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
	tmp->outpipe = NULL;
	tmp->inpipe = NULL;
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
int			len_split3d(t_cmd *cmd)
{
	int		pipe;
	t_cmd	*tmp;

	tmp = cmd;
	pipe = 0;
	if (tmp && !ft_strcmp(tmp->input, "|")) //si le premier est | erreur
		return (-1);
	while (tmp)
	{
		if (!ft_strcmp(tmp->input, "|") && (!tmp->next || !tmp->next->next)) // si le derniere est un | erreur
			return (-1);
		else if (!ft_strcmp(tmp->input, "|") && !ft_strcmp(tmp->next->next->input, "|")) // si il y a un | et que celui d'apres et un | erreur
			return (-2);
		else if (!ft_strcmp(tmp->input, "|"))
			pipe++;
		tmp = tmp->next;
	}
	if (pipe == 0)
		return (0);
	return (pipe + 1);
}
*/

int			len_split3d(t_cmd *cmd)
{
	int		pipe;
	t_cmd	*tmp;

	tmp = cmd;
	pipe = 0;
	if (tmp && !ft_strcmp(tmp->input, "|")) //si le premier est | erreur
		return (-1);
	while (tmp)
	{
		if (!ft_strcmp(tmp->input, "|") && !tmp->next) // si le derniere est un | erreur
			return (-1);
		else if (!ft_strcmp(tmp->input, "|") && !ft_strcmp(tmp->next->input, " ") && !tmp->next->next)
			return (-1);
		else if (!ft_strcmp(tmp->input, "|") && !ft_strcmp(tmp->next->input, " ") && !ft_strcmp(tmp->next->next->input, "|"))
			return (-2);		
		else if (!ft_strcmp(tmp->input, "|") && ft_strcmp(tmp->next->input, " ") && !ft_strcmp(tmp->next->input, "|")) // si il y a un | et que celui d'apres et un | erreur
			return (-2);
		else if (!ft_strcmp(tmp->input, "|"))
			pipe++;
		tmp = tmp->next;
	}
	if (pipe == 0)
		return (0);
	return (pipe + 1);
}


int				len_tabsplit3d(t_cmd *cmd)
{
	t_cmd		*tmp;
	int			ret;

	ret = 0;
	tmp = cmd;
	while (tmp)
	{
		if (!ft_strcmp(tmp->input, "|"))
			return (ret);
		ret++;
		tmp = tmp->next;
	}
	return (ret);
}

/*
int				no_redi(char *input)
{
	return (!ft_strcmp(input, "\">\"") || !ft_strcmp(input, "\"<\"")
	|| !ft_strcmp(input, "\">>\"") || !ft_strcmp(input, "'>'")
	|| !ft_strcmp(input, "'<'") || !ft_strcmp(input, "'>>'"));
}
 */

void			tab2_3d(t_cmd *cmd, t_temp *tmp)
{
	t_cmd		*tmpo;
	int			i;
	int			k;
	int			len;


	i = 0;
	tmpo = cmd;
	while (tmpo)
	{
		k = 0;
		len = len_tabsplit3d(tmpo);
		printf("estoy aqui\n len ---[%d] \n", len);
		tmp->outpipe[i] = (char**)malloc(sizeof(char *) * len + 1);
		tmp->inpipe[i] = (char**)malloc(sizeof(char *) * len + 1);
		while (k < len)
		{
			tmp->inpipe[i][k] = ft_strdup(tmpo->input);
			tmp->outpipe[i][k] = ft_strdup(tmpo->output);
			k++;
			if (tmpo->next)
				tmpo = tmpo->next;
		}
		tmp->outpipe[i][k] = NULL;		
		tmp->inpipe[i][k] = NULL;	
		i++;
		tmpo = tmpo->next;
	}
	tmp->outpipe[i] = NULL;
	tmp->inpipe[i] = NULL;
}

int				split3d(t_cmd *cmd, t_temp *tmp)
{
	int			ret;

	if ((ret = len_split3d(cmd)) == 0)//
		return (0);
	if (ret < 0)
	{
		printf("saliendo\n");
		return (-1);
	}
	tmp->outpipe = (char***)malloc(sizeof(char**) * ret + 1);
	tmp->inpipe = (char***)malloc(sizeof(char**) * ret + 1);
	tab2_3d(cmd, tmp);
	//podriamos hacer los tableros, despues de los tableros, reformar la lista, y de esa lista volver a sacar el nuevo tablero
	// a partir de la lista ya hecha con la funcion que tenemos de pasar de lista a tablero.
	int		o = 0;
	while (tmp->outpipe[o])
	{
		printf("tab outpipe[%d]\n",o);
		printftab(tmp->outpipe[o]);
		o++;
	}
	o = 0;
	while (tmp->outpipe[o])
	{
		printf("tab inpipe[%d]\n",o);
		printftab(tmp->inpipe[o]);
		o++;
	}
	return (1);
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
		separator_string(&cmd, tabcmd[i], tmp);
		printflist(cmd);
		(cmd) ? split3d(cmd, tmp) : 0;



		(cmd) ? tmp->strcmd = llist_astring(cmd, tmp->strcmd, 1) : 0;


//notre tab 3d
// echo tmp->strcmd[0] = echo key 0 sinon key 1
//		printftab(tmp->strcmd);
	//	exit(1);
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
