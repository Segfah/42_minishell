/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_env_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 00:50:50 by corozco           #+#    #+#             */
/*   Updated: 2020/08/22 15:43:01 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** int key est pour choisir si je dois afficher le env(1) ou l'export(X!=1)
*/

void			print_list(t_lists *head, int key)
{
	t_lists		*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		if (key == 1)
		{
			if (tmp->data != NULL)
				ft_printf("%s=%s\n", tmp->name, tmp->data);
		}
		else
		{
			ft_printf("%s=", tmp->name);
			if (tmp->data == NULL)
				write(1, "''\n", 3);
			else
			{
				(tmp->data[0] != 0 && tmp->data != NULL) ?
					ft_printf("%s\n", tmp->data) : write(1, "''\n", 3);
			}
		}
		tmp = tmp->next;
	}
}

int				lback(t_lists **alst, char *str, char *str2)
{
	t_lists		*tmp;
	t_lists		*new;

	if (!(new = ft_memalloc(sizeof(t_lists))))
		return (-1);
	if (!(new->name = ft_strdup(str)))
		return (-1);
	if (str2)
	{
		if (!(new->data = ft_strdup(str2)))
			return (-1);
	}
	else
		new->data = NULL;
	new->next = NULL;
	tmp = *alst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->next = NULL;
	return (0);
}

static void		addfront(t_lists **head, char *str, char *str2)
{
	t_lists		*new;

	if (!(new = malloc(sizeof(t_lists))))
		exit(1);
	if (!(new->name = ft_strdup(str)))
		exit(1);
	if (str2)
	{
		if (!(new->data = ft_strdup(str2)))
			exit(1);
	}
	else
		new->data = NULL;
	new->next = *head;
	*head = new;
}

/*
**	Fait une copie d'une liste ch....
*/

void			cpy_env(t_lists **cpy, t_lists *list)
{
	t_lists		*tmplist;

	*cpy = NULL;
	tmplist = list;
	while (tmplist != NULL)
	{
		addfront(cpy, tmplist->name, tmplist->data);
		tmplist = tmplist->next;
	}
}
