/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 14:02:09 by lryst             #+#    #+#             */
/*   Updated: 2020/12/01 10:09:52 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tilde(t_cmd *cmd, t_temp *tmp)
{
	if (search_env("HOME", tmp, 1, NULL) == 0)
		cmd->output = ft_strdup(tmp->hnull);
	else
		search_env("HOME", tmp, 0, &cmd->output);
}

int		check_node(t_cmd *cmd, t_temp *temp)
{
	if (cmd->input[0] == '$')
		dollar_cmd(cmd, temp->varenv);
	else if (cmd->input[0] == '\\')
		slash_cmd(cmd);
	else if (cmd->input[0] == '\'')
		single_cote_cmd(cmd);
	else if (cmd->input[0] == '"')
		dcote_cmd(cmd, temp->varenv);
	else if (!ft_strcmp("~", cmd->input))
		tilde(cmd, temp);
	else
	{
		if (!(cmd->output = ft_strdup(cmd->input)))
			return (-1);
	}
	return (0);
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
		if (!(tmp->input = ft_strdup(input)))
			return (NULL);
		if (check_node(tmp, temp) == -1)
		{
			free_cmd(tmp);
			general_free(temp);
		}
	}
	else
		tmp->input = NULL;
	tmp->next = NULL;
	return (tmp);
}
