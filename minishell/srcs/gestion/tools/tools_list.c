/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_env_export.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 00:50:50 by corozco           #+#    #+#             */
/*   Updated: 2020/08/19 04:48:22 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_node(t_lists *node)
{
	(node->name != NULL) ? free(node->name) : 0;
	(node->data != NULL) ? free(node->data) : 0;
	free(node);
}

void			free_list(t_lists *test)
{
	t_lists		*tmp;

	while (test != NULL)
	{
		tmp = test->next;
		free_node(tmp);
		test = tmp;
	}
}
