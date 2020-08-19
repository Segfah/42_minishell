/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_env_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 00:50:50 by corozco           #+#    #+#             */
/*   Updated: 2020/08/19 03:05:18 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** + 1 pour effacer le =; si on a besoin du "=" enlever le +1, il va etre...
** dans la data (2 content)
** arreglar los exit(1); y cambiarlos por return (-1)
*/

void			print_list(t_lists *head)
{
	t_lists		*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		ft_printf("%s=", tmp->name);
		ft_printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
}

void			addfront(t_lists **head, char *str, char *str2)
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

void			free_list(t_lists *test)
{
	t_lists		*tmp;

	while (test != NULL)
	{
		tmp = test->next;
		if (test->name)
			free(test->name);
		if (test->data)
			free(test->data);
		free(test);
		test = tmp;
	}
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
