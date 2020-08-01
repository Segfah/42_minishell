/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principal_parcing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 02:30:51 by corozco           #+#    #+#             */
/*   Updated: 2020/08/01 04:44:50 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**suite de la fonction gestion_cd, cette fonction gere la commande cd en mettant le chemin relatif ou absolu...
**mais aussi le ".." et "."
*/
void	gestion_cd(char *str)
{
	char *path;
	int i;

	i = 2;
	if (ft_strncmp(str, "cd ", 3) == 0)
	{
		if (!(path = (char*)malloc(sizeof(char) * ft_strlen(str) - 2)))
		{
			ft_printf("gestion_cd2, error malloc\n");
			exit (0);
		}
		while (str[i++] != '\0')
			path[i - 3] = str[i];
		if (chdir(path) != 0)
			ft_printf("cd: no such file or directory: %s\n", path);
	}
	else
		ft_printf("minishell: command not found: %s\n", str);
}

/*
** Cette fonction efface les espaces et les \t,
**		Alerte!! La fonction n'est pas fini, elle ne les doit pas supprimer si...
**		...il y a des "  " ou de '  '
*/
static void		clean_str(char *str)
{
	int			i;
	int			j;

	j = 0;
	while (str[j] == ' ' || str[j] == '\t')
		j++;
	i = 0;
	while (str[j])
	{											//####################################################################################################################corozco
		if (str[j] != ' ' || str[j + 1] != ' ') // l'idee c'est de mettre une variable flag qui prend la valeur de 1 s'il trouve un " et un ", et si elle est active...
			str[i++] = str[j];					// la fonction ne devra pas effacer les espaces
		j++;									//if (str[j] != ' ' || str[j + 1] != ' ' && flag != 1) 
	}											//####################################################################################################################corozco
	str[i] = 0;
	while (str[--i] == ' ' || str[i] == '\t')
		str[i] = 0;
}

/*
** Elle cherche dans le tableau de commandes, si la commande existe.
** ensuite elle free la string du tableau free(tabcmd[i]) 
*		Alerte, en testant je me suis rendu compte que dans bash, on peux appeler les ...
*		... les commandes de plusier manieres exo PWD pwd Pwd PwD pWd  (il faut fait les mettre en minuscules?)
*/

static void		gestion_line(char **tabcmd, t_temp *tmp, int i)
{
	while (tabcmd[++i])
	{
		clean_str(tabcmd[i]);
		if (ft_strcmp(tabcmd[i], "exit") == 0)
			exit(0);
		if (ft_strncmp(tabcmd[i], "cd", 2) == 0)
			gestion_cd(tabcmd[i]);
		else if (gestion_pwd(tabcmd, tmp, i))
			;
		else if (tabcmd[i][0] == '\0')
			;
		else
			ft_printf("minishell: command not found: %s\n", tabcmd[i]);
		free(tabcmd[i]);
	}
}

/*
** ft_getline reçoit avec l'aide du get_next_line la ligne avec les commandes...
** ...et lance aussi le parcing 
*/

void			ft_getline(t_temp *tmp)
{
	char		*line;

	if (ft_gnl(0, &line) == -1 || (tmp->tabcmd = ft_split(line, ';')) == NULL)
		exit(1);
	gestion_line(tmp->tabcmd, tmp, -1);
	free(tmp->tabcmd);
	free(line);
}
