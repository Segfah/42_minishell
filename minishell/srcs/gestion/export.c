/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 02:32:22 by corozco           #+#    #+#             */
/*   Updated: 2020/08/06 05:14:44 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			range_export(t_lists *la)
{
	t_lists *tmp;
	t_lists *tmp1;
	t_lists *tmp3;
	char	*s1;
	char	*s2;

	tmp = la;
	while (tmp->next != NULL)
	{
		tmp3 = tmp;
//		s1 = tmp->name;
//		s2 = tmp->data;
		tmp1 = tmp->next;
		while (tmp1 != NULL)
		{
			if (ft_strcmp(tmp1->name, tmp3->name) > 0)
			{
				tmp3 = tmp1;
//				s1 = tmp3->name;
//				s2 = tmp3->data;
			}
			tmp1 = tmp1->next;
		}
		s1 = tmp->name;
		s2 = tmp->data;
		tmp->name = tmp3->name;
		tmp->data = tmp3->data;
		tmp3->name = s1;
		tmp3->data = s2;
//		tmp3->name = tmp->name;
//		tmp3->data = tmp->data;
		tmp = tmp->next;
	}
}

void			cpy_env(t_lists **cpy, t_lists *list)
{
	t_lists *tmplist;

	*cpy = NULL;
	tmplist = list;
	while (tmplist != NULL)
	{
		add_list_front(cpy, tmplist->name, tmplist->data);
		tmplist = tmplist->next;
	}
}

void		gestion_export(t_temp *tmp)
{
	int		i;

	i = 0;
	while (tmp->strcmd[i])
		i++;
	if (i == 1)
	{
		cpy_env(&tmp->exportenv, tmp->varenv);
		range_export(tmp->exportenv);
		gestion_env(tmp->exportenv);
		free_list(tmp->exportenv);
	}
	else
		ft_printf("En creacion\n");
}
