/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_env_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 00:50:50 by corozco           #+#    #+#             */
/*   Updated: 2020/08/09 03:57:02 by corozco          ###   ########.fr       */
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


void			add_list_front(t_lists **head, char *str, char *str2)
{
	t_lists		*new;
	int			i;

	if (!(new = malloc(sizeof(t_lists))))
		exit(1);
	if (str2 == NULL)
	{
		if (!(new->data = ft_strdup(ft_strchr(str, '=') + 1)))
			exit(1);
		i = 0;
		while (str[i] != '=')
			i++;
		str[i] = '\0';
		if (!(new->name = ft_strdup(str)))
			exit(1);
	}
	else
	{
		if (!(new->data = ft_strdup(str2)))
			exit(1);
		if (!(new->name = ft_strdup(str)))
			exit(1);
	}
	new->next = *head;
	*head = new;
}

void			free_list(t_lists *test)
{
	t_lists		*tmp;

	while (test != NULL)
	{
		tmp = test->next;
		free(test->name);
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
	t_lists *tmplist;

	*cpy = NULL;
	tmplist = list;
	while (tmplist != NULL)
	{
		add_list_front(cpy, tmplist->name, tmplist->data);
		tmplist = tmplist->next;
	}
}
