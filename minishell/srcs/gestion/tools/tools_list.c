/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_env_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 00:50:50 by corozco           #+#    #+#             */
/*   Updated: 2020/08/30 01:58:35 by corozco          ###   ########.fr       */
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
	if (previous->name && ft_strcmp(previous->name, strkey) == 0)
	{
		list = previous->next;
		free_node(previous);
		return ;
	}
	tmp = previous->next;
	while (tmp != NULL)
	{
		if (tmp->name && ft_strcmp(tmp->name, strkey) == 0)
		{
			previous->next = tmp->next;
			free_node(tmp);
			return ;
		}
		previous = tmp;
		tmp = tmp->next;
	}
}

void			free_node(t_lists *node)
{
	ft_free(node->name);
	node->name = NULL;
	ft_free(node->data);
	node->data = NULL;
	ft_free(node);
	node = NULL;
}

void			free_list(t_lists *test)
{
	t_lists		*tmp;

	while (test != NULL)
	{
		tmp = test->next;
		free_node(test);
		test = NULL;
		test = tmp;
	}
}
