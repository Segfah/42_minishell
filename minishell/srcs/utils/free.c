/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 17:58:38 by lryst             #+#    #+#             */
/*   Updated: 2020/11/20 14:17:38 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				ft_free_double_tab(char **tab)
{
	int				i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			ft_free(tab[i++]);
		free(tab);
	}
	tab = NULL;
}

void				ft_free_triple_tab(char ***tab3d)
{
	int				i;

	i = 0;
	if (tab3d)
	{
		while (tab3d[i])
			ft_free_double_tab(tab3d[i++]);
		free(tab3d);
	}
	tab3d = NULL;
}

void				free_node_cmd(t_cmd *node)
{
	node->input ? ft_free(node->input): 0;
	node->input = NULL;
	node->output ?ft_free(node->output): 0;
	node->output = NULL;
	node ? ft_free(node) : 0;
	node = NULL;
}

void				free_cmd(t_cmd *cmd)
{
	t_cmd			*tmp;

	while (cmd != NULL)
	{
		tmp = cmd->next;
		free_node_cmd(cmd);
		cmd = tmp;
	}
	ft_free(cmd);
}

void				free_export_tab(t_temp *tmp)
{
	ft_free(tmp->tab[0]);
	tmp->tab[0] = NULL;
	ft_free(tmp->tab[1]);
	tmp->tab[1] = NULL;
}
