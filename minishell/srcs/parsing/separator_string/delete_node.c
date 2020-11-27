/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_node.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 17:54:33 by lryst             #+#    #+#             */
/*   Updated: 2020/11/27 18:32:46 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_null_node(t_cmd **cmd)
{
	t_cmd *save;
	t_cmd *tmp;

	tmp = *cmd;
	while (tmp)
	{
		save = NULL;
		if (tmp->next && (tmp->next->output == NULL ||
		tmp->next->input == NULL))
		{
			save = tmp->next->next;
			ft_lstdelone_cmd(tmp->next);
			tmp->next = save;
		}
		else
			tmp = tmp->next;
	}
}

void	ft_lstdelone_cmd(t_cmd *lst)
{
	if (lst)
	{
		if (lst->input)
			ft_free(lst->input);
		lst->input = NULL;
		if (lst->output)
			ft_free(lst->output);
		lst->output = NULL;
		ft_free(lst);
		lst = NULL;
	}
}

void	remove_space_node(t_cmd **cmd)
{
	t_cmd *save;
	t_cmd *tmp;

	tmp = *cmd;
	while (tmp)
	{
		save = NULL;
		if (tmp->next && (ft_strcmp(tmp->next->input, " ") == 0) &&
		(tmp->next->next == NULL ||
		(ft_strcmp(tmp->next->next->input, " ") == 0)))
		{
			save = tmp->next->next;
			ft_lstdelone_cmd(tmp->next);
			tmp->next = save;
		}
		else
			tmp = tmp->next;
	}
}

void	remove_all_space_node(t_cmd **cmd)
{
	t_cmd *save;
	t_cmd *tmp;

	tmp = *cmd;
	while (tmp)
	{
		save = NULL;
		if (tmp->next && (ft_strcmp(tmp->next->input, " ") == 0))
		{
			save = tmp->next->next;
			ft_lstdelone_cmd(tmp->next);
			tmp->next = save;
		}
		else
			tmp = tmp->next;
	}
}
