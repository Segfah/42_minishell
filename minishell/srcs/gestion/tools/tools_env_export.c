/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_env_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 00:50:50 by corozco           #+#    #+#             */
/*   Updated: 2020/11/22 18:19:51 by lryst            ###   ########.fr       */
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
			ft_printf("declare -x %s", tmp->name);
			if (tmp->data == NULL)
				write(1, "\n", 1);
			else
				ft_printf("=\"%s\"\n", tmp->data);
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

static int		addfront(t_lists **head, char *str, char *str2)
{
	t_lists		*new;

	if (!str)
		return (1);
	if (!(new = malloc(sizeof(t_lists))))
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
	new->next = *head;
	*head = new;
	return (0);
}

/*
**	Fait une copie d'une liste ch....
*/

int				cpy_env(t_lists **cpy, t_lists *list)
{
	t_lists		*tmplist;

	*cpy = NULL;
	tmplist = list;
	while (tmplist != NULL)
	{
		if (addfront(cpy, tmplist->name, tmplist->data) == -1)
		{
			free_list(list);
			list = NULL;
			free_list(*cpy);
			*cpy = NULL;
			return (-1);
		}
		tmplist = tmplist->next;
	}
	return (0);
}

int				change_list(t_lists *head, char *ss, char *new, t_temp *t)
{
	t_lists		*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		if (tmp->name && ft_strcmp(tmp->name, ss) == 0)
		{
			ft_free(tmp->data);
			if (new != NULL)
			{
				if (!(tmp->data = ft_strdup(new)))
					general_free(t);
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
