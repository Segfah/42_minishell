/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 14:02:09 by lryst             #+#    #+#             */
/*   Updated: 2020/10/20 14:30:47 by lryst            ###   ########.fr       */
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
		if (tmp->next && (tmp->next->output == NULL || tmp->next->input == NULL))
		{
			save = tmp->next->next;
			ft_lstdelone_cmd(tmp->next);
			tmp->next = save;
		}
		tmp = tmp->next;
	}
}

void	check_node(t_cmd *cmd, t_temp *temp)
{
	if (cmd->input[0] == '$')
		dollar_cmd(cmd, temp->varenv);
	else if (cmd->input[0] == '\\')
		slash_cmd(cmd);
	else if (cmd->input[0] == '\'')
		single_cote_cmd(cmd);
	else if (cmd->input[0] == '"')
		double_cote_cmd(cmd, temp->varenv);
	else
		cmd->output = ft_strdup(cmd->input);
}

void	ft_lstadd_back_cmd(t_cmd **alst, t_cmd *new)
{
	t_cmd	*tmp;

	tmp = NULL;
	if (new)
	{
		if (!alst || !(*alst))
		{
			*alst = new;
			return ;
		}
		tmp = *alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

t_cmd	*ft_lstnew_cmd(char *input, t_temp *temp)
{
	t_cmd	*tmp;

	if (!(tmp = malloc(sizeof(t_cmd))))
		return (NULL);
	if (input)
	{
		tmp->input = ft_strdup(input);
		check_node(tmp, temp);
	}
	else
		tmp->input = NULL;
	tmp->next = NULL;
	return (tmp);
}
