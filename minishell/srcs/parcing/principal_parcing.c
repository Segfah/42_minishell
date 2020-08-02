/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   principal_parcing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 02:30:51 by corozco           #+#    #+#             */
/*   Updated: 2020/08/02 23:24:09 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** cherche s'il y a une ou plusieres " o ' et return le nombre des espaces
** que la clean_str doit garder
*/

int				single_or_double_quote(char *str, int i, char c)
{
	int			k;

	k = 1;
	while (str[++i])
	{
		if (str[i] == c)
			return (k + 1);
		k++;
	}
	return (0);
}

/*
** fonction qui trouve un " ou un ' et active le flag correspondant
*/

void			skyp_spaces(char *str, int j, int *k)
{
	int			flag34;
	int			flag39;

	flag34 = 0;
	flag39 = 0;
	if (str[j] == 34 || str[j] == 39)
	{
		if (str[j] == 34)
			flag34 = (flag34 == 0) ? 1 : 0;
		else
			flag39 = (flag39 == 0) ? 1 : 0;
		if (flag34 == 1 || flag39 == 1)
			*k = single_or_double_quote(str, j, str[j]);
	}
}

/*
** Cette fonction efface les espaces et les \t
*/

void			clean_str(char *str)
{
	int			i;
	int			j;
	int			k;

	j = 0;
	k = 0;
	while (str[j] == ' ' || str[j] == '\t')
		j++;
	i = 0;
	while (str[j])
	{
		skyp_spaces(str, j, &k);
		if ((str[j] != ' ' || str[j + 1] != ' ') && k == 0)
			str[i++] = str[j];
		if (k > 0)
		{
			str[i++] = str[j];
			k--;
		}
		j++;
	}
	str[i] = 0;
	while (str[--i] == ' ' || str[i] == '\t')
		str[i] = 0;
}

/*
** Elle cherche dans le tableau de commandes, si la commande existe
** ensuite elle free la string du tableau free(tabcmd[i])
*/

static void		gestion_line(char **tabcmd, t_temp *tmp, int i, char **envp)
{
	while (tabcmd[++i])
	{
		clean_str(tabcmd[i]);
		if (ft_strcmp(tabcmd[i], "exit") == 0)
			exit(0);
		if (ft_strncmp(tabcmd[i], "cd", 2) == 0)
			gestion_cd(tabcmd[i]);
		if (ft_strcmp(tabcmd[i], "env") == 0)
			gestion_env(envp);
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

void			ft_getline(t_temp *tmp, char **envp)
{
	char		*line;

	if (ft_gnl(0, &line) == -1 || (tmp->tabcmd = ft_split(line, ';')) == NULL)
		exit(1);
	gestion_line(tmp->tabcmd, tmp, -1, envp);
	free(tmp->tabcmd);
	free(line);
}
