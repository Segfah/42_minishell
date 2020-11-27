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
		{
			free(tab[i]);
			tab[i++] = NULL;
		}
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

void				free_cmd(t_cmd *cmd)
{
	t_cmd			*tmp;

	while (cmd != NULL)
	{
		tmp = cmd->next;
		cmd->input ? free(cmd->input) : 0;
		cmd->input = NULL;
		cmd->output ? free(cmd->output) : 0;
		cmd->output = NULL;
		cmd ? free(cmd) : 0;
		cmd = NULL;
		cmd = tmp;
	}
	ft_free(cmd);
	cmd = NULL;
}

void				free_export_tab(t_temp *tmp)
{
	ft_free(tmp->tab[0]);
	tmp->tab[0] = NULL;
	ft_free(tmp->tab[1]);
	tmp->tab[1] = NULL;
}
