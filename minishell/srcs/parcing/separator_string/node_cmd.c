/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 14:02:09 by lryst             #+#    #+#             */
/*   Updated: 2020/09/30 18:58:09 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstdelone_cmd(l_cmd *lst)
{
	if (lst)
	{
		if (lst->input)
			free(lst->input);
		if (lst->output)
			free(lst->output);
		free(lst);
	}
}
void	remove_space_node(l_cmd **cmd)
{
	l_cmd *save;
	l_cmd *tmp;
	
	tmp = *cmd;
	while (tmp)
	{
		save = NULL;
		if (tmp->next && (ft_strcmp(tmp->next->output, " ") == 0) && (ft_strcmp(tmp->next->next->output, " ") == 0))
		{
			
			save = tmp->next->next;
			ft_lstdelone_cmd(tmp->next);
			tmp->next = save;
			
		}
		tmp = tmp->next;
	}
	write(1, "coucou\n", 7);
}


void	remove_null_node(l_cmd **cmd)
{
	l_cmd *save;
	l_cmd *tmp;
	
	tmp = *cmd;
	while (tmp)
	{
		save = NULL;
		if (tmp->next && tmp->next->output == NULL)
		{
			
			save = tmp->next->next;
			ft_lstdelone_cmd(tmp->next);
			tmp->next = save;
			
		}
		tmp = tmp->next;
	}
	write(1, "coucou\n", 7);
}

void	check_node(l_cmd *cmd, t_temp *temp)
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

void	ft_lstadd_back_cmd(l_cmd **alst, l_cmd *new)
{
	l_cmd	*tmp;

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

l_cmd	*ft_lstnew_cmd(char *input, t_temp *temp)
{
	l_cmd	*tmp;

	if (!(tmp = malloc(sizeof(l_cmd))))
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