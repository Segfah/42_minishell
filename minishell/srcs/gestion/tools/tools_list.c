/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_env_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 00:50:50 by corozco           #+#    #+#             */
/*   Updated: 2020/08/30 01:28:56 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			deletenode(t_lists *list, char *strkey)
{
	t_lists		*tmp;
	t_lists		*previous;

	if (list == NULL)
		return ;
	previous = list;
	if (ft_strcmp(previous->name, strkey) == 0)
	{
		list = previous->next;
		free_node(previous);
//		previous = NULL;
		return ;
	}
	tmp = previous->next;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, strkey) == 0)
		{
			previous->next = tmp->next;
			free_node(tmp);
//			tmp = NULL;
			return ;
		}
		previous = tmp;
		tmp = tmp->next;
	}
}

void			free_node(t_lists *node)
{
	(node->name != NULL) ? free(node->name) : 0;
	node->name = NULL;
	(node->data != NULL) ? free(node->data) : 0;
	node->data = NULL;
	free(node);
	node = NULL;
}

void			free_list(t_lists *test)
{
	t_lists		*tmp;

	while (test != NULL)
	{
		tmp = test->next;
		free_node(test);
		test = tmp;
	}
}
