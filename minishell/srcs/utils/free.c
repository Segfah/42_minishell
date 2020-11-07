/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 17:58:38 by lryst             #+#    #+#             */
/*   Updated: 2020/10/15 14:46:22 by lryst            ###   ########.fr       */
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
		tab = NULL;
	}
}

void				ft_free_triple_tab(char ***tab3d)
{
	int				i;

	i = 0;
	if (tab3d)
	{
		while(tab3d[i])
			ft_free_double_tab(tab3d[i++]);
		free(tab3d);
		tab3d = NULL;
	}
}

void				free_node_cmd(t_cmd *node)
{
	ft_free(node->input);
	ft_free(node->output);
	ft_free(node);
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
