/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 02:32:22 by corozco           #+#    #+#             */
/*   Updated: 2020/11/19 11:13:11 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_cortar(char *tab[2], char *str)
{
	int			i;
	char		*ss;

	if ((i = check_env(str, 1)) == -1)
		return (-2);
	else if (i == 0)
	{
		if (!(tab[0] = ft_strdup(str)))
			return (-1);
		tab[1] = NULL;
	}
	else
	{
		ss = ft_strchr(str, '=');
		if (!(tab[1] = ft_strdup(ss + 1)))
			return (-1);
		str[ss - str] = 0;
		if (!(tab[0] = ft_strdup(str)))
			return (-1);
		str[(int)ft_strlen(str)] = '=';
	}
	return (0);
}

/*
** liste -> tmp->varenv
** char* tmp->hnull
** char* tmp->prompt
*/

void			general_free(t_temp *tmp)
{
	(!tmp->varenv) ? free_list(tmp->varenv) : 0;
	(!tmp->hnull) ? ft_free(tmp->hnull) : 0;
	(!tmp->prompt) ? ft_free(tmp->prompt) : 0;
	(!tmp->env) ? ft_free(tmp->env) : 0;
	(!tmp->tabcmd) ? ft_free(tmp->tabcmd) : 0;
	(!tmp->strcmd) ? ft_free_double_tab(tmp->strcmd) : 0;
	(!tmp->strcmdin) ? ft_free_double_tab(tmp->strcmdin) : 0;
	(!tmp->cpytab) ? ft_free_double_tab(tmp->cpytab) : 0;
	(!tmp->inpipe) ? ft_free_triple_tab(tmp->inpipe) : 0;
	(!tmp->outpipe) ? ft_free_triple_tab(tmp->outpipe) : 0;
	(!tmp->cpypipe) ? ft_free_triple_tab(tmp->cpypipe) : 0;
	write(2, "Error: Malloc\n", 14);
	exit(1);
	ft_free(tmp->tab[0]);
	ft_free(tmp->tab[1]);
	(tmp->exportenv != NULL) ? free_list(tmp->exportenv) : 0;
}

int				export_arg(t_temp *tmp, int ret, int i)
{
	if ((ret = ft_cortar(tmp->tab, tmp->strcmd[i])) == -2)
	{
		g_ret = 1;
		ft_fprintf(2, "minishell: export: `%s': not a valid identifier\n",
			tmp->strcmd[i]);
		return (0);
	}
	else if (ret == -1)
		return (-1);
	else
	{
		if ((ret = search_env(tmp->tab[0], tmp, 1, NULL)) == 0)
		{
			if ((lback(&tmp->varenv, tmp->tab[0], tmp->tab[1])) == -1)
				return (-1);
		}
		else if (ret == 1 && tmp->tab[1] != NULL)
			change_list(tmp->varenv, tmp->tab[0], tmp->tab[1], tmp);
	}
	return (0);
}

void			gestion_export_2(t_temp *tmp)
{
	int ret;

	if (tmp->varenv)
	{
		if ((ret = cpy_env(&tmp->exportenv, tmp->varenv)) == -1)
			general_free(tmp);
		if (ret == 0)
		{
			range_export(tmp->exportenv);
			print_list(tmp->exportenv, 0);
			free_list(tmp->exportenv);
		}
	}
	tmp->exportenv = NULL;
	(tmp->flag[1] == 1) ? dup2(tmp->oldfd, 1) : 0;
}

void			gestion_export(t_temp *tmp, int i)
{
	g_ret = 0;
	while (tmp->strcmd[i])
		i++;
	if (i == 1 || (i = 0))
	{
		if (tmp->flag[1] == 1)
		{
			tmp->oldfd = dup(1);
			dup2(tmp->fd, 1);
		}
		gestion_export_2(tmp);
	}
	else
	{
		while (tmp->strcmd[++i])
		{
			(export_arg(tmp, 0, i) == -1) ? general_free(tmp) : 0;
			free_export_tab(tmp);
		}
	}
}
