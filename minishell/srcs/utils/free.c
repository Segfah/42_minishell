/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 17:58:38 by lryst             #+#    #+#             */
/*   Updated: 2020/09/15 16:27:44 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				ft_free(char *str)
{
	free(str);
	str = NULL;
}

void				ft_free_double_tab(char **tab)
{
	int i;

	i = 0;
	while(tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	free(tab);
	tab = NULL;
}

void				free_node_cmd(l_cmd *node)
{
	(node->input != NULL) ? free(node->input) : 0;
	node->input = NULL;
	(node->output != NULL) ? free(node->output) : 0;
	node->output = NULL;
	free(node);
	node = NULL;
}

void				free_cmd(l_cmd *cmd)
{
	l_cmd		*tmp;

	while (cmd != NULL)
	{
		tmp = cmd->next;
		free_node_cmd(cmd);
		cmd = tmp;
	}
	free(cmd);
}

void			free_tmps(char **tabcmd, int i, t_temp *tmp)
{
	int			a;

	a = 0;
	while (tmp->strcmd[a])
	{
		free(tmp->strcmd[a]);
		tmp->strcmd[a++] = NULL;
	}
	free(tmp->strcmd);
	tmp->strcmd = NULL;
	free(tabcmd[i]);
	tabcmd[i] = NULL;
}