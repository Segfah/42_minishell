/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 02:32:22 by corozco           #+#    #+#             */
/*   Updated: 2020/10/21 18:20:02 by corozco          ###   ########.fr       */
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

void			general_free(t_temp *tmp)
{
	ft_free(tmp->env);
	ft_free(tmp->prompt);
	ft_free(tmp->tab[0]);
	ft_free(tmp->tab[1]);
	(tmp->varenv != NULL) ? free_list(tmp->varenv) : 0;
	(tmp->exportenv != NULL) ? free_list(tmp->exportenv) : 0;
	ft_free(tmp->hnull);
	ft_printf("Error: Malloc\n");
	exit(1);
}

int				export_arg(t_temp *tmp, int ret, int i, int key)
{
	if ((ret = ft_cortar(tmp->tab, tmp->strcmd[i])) == -2)
	{
		if (key)
			exit(20);
		ft_printf("minishell: export: `%s': not a valid identifier\n",
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
		{
			if ((change_list(tmp->varenv, tmp->tab[0], tmp->tab[1])) == -1)
				return (-1);
		}
	}
	return (0);
}

void			free_export_tab(t_temp *tmp)
{
	ft_free(tmp->tab[0]);
	tmp->tab[0] = NULL;
	ft_free(tmp->tab[1]);
	tmp->tab[1] = NULL;
//	if (tmp->tab[1] != NULL)
//	{
//		free(tmp->tab[1]);
//		tmp->tab[1] = NULL;
//	}
}

void			gestion_export(t_temp *tmp, int i, int key)
{
	while (tmp->strcmd[i])
		i++;
	if (i == 1 || (i = 0))
	{
		if (tmp->flag[1] == 1)
		{
			tmp->oldfd = dup(1);
			dup2(tmp->fd, 1);
		}
		(cpy_env(&tmp->exportenv, tmp->varenv) == -1) ? general_free(tmp) : 0;
		range_export(tmp->exportenv);
		print_list(tmp->exportenv, 0);
		free_list(tmp->exportenv);
		tmp->exportenv = NULL;
		(tmp->flag[1] == 1) ? dup2(tmp->oldfd, 1) : 0;
	}
	else
	{
		while (tmp->strcmd[++i])
		{
			(export_arg(tmp, 0, i, key) == -1) ? general_free(tmp) : 0;
			free_export_tab(tmp);
		}
	}
//	(tmp->flag[1]) ? close(tmp->fd) : 0;
}
