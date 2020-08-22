/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 02:32:22 by corozco           #+#    #+#             */
/*   Updated: 2020/08/22 15:35:20 by corozco          ###   ########.fr       */
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

void			gestion_export(t_temp *tmp)
{
	int			i;
	int			ret;
	char		*tab[2];

	i = 0;
	ret = 0;
	while (tmp->strcmd[i])
		i++;
	if (i == 1)
	{
		cpy_env(&tmp->exportenv, tmp->varenv);
		range_export(tmp->exportenv);
		print_list(tmp->exportenv, 0);
		free_list(tmp->exportenv);
	}
	else
	{
		i = 0;
		while (tmp->strcmd[++i])
		{
			if ((ret = ft_cortar(tab, tmp->strcmd[i])) == -2)
			{
				ft_printf("minishell: export: `%s': not a valid identifier\n",
						tmp->strcmd[i]);
				break ;
			}
			else if (ret == -1)
				exit(1); //error malloc
			else
			{
				if ((ret = search_env(tab[0], tmp, 1, NULL)) == 0)
				{
					if ((lback(&tmp->varenv, tab[0], tab[1])) == -1)
						exit(1); // error malloc
				}
				else if (ret == 1 && tab[1] != NULL)
				{
					deletenode(tmp->varenv, tab[0]);
					if ((lback(&tmp->varenv, tab[0], tab[1])) == -1)
						exit(1); // error malloc
				}
			}
			free(tab[0]);
			if (tab[1] != NULL)
				free(tab[1]);
		}
	}
}
