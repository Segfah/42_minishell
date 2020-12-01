/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dcote_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 10:11:15 by lryst             #+#    #+#             */
/*   Updated: 2020/12/01 10:23:03 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dcote_fill_slash(t_cmd *cmd, int *i, int *j)
{
	int save;
	int size;

	save = 0;
	size = 0;
	while (cmd->input[*i] && cmd->input[*i] == '\\')
	{
		save++;
		(*i)++;
	}
	while (size++ < (save / 2))
		cmd->output[(*j)++] = '\\';
	if (save % 2 == 1)
	{
		if (cmd->input[*i] && (cmd->input[*i] == '"' || cmd->input[*i] == '$'))
			cmd->output[(*j)++] = cmd->input[(*i)++];
		else if (save == 1 && (cmd->input[*i] != '"' || cmd->input[*i] != '$'))
		{
			cmd->output[(*j)++] = '\\';
			cmd->output[(*j)++] = cmd->input[(*i)++];
		}
	}
	else
		while (size++ < (save / 2))
			cmd->output[(*j)++] = '\\';
}

void	dcote_fill_dollar2(t_lists *revar, char *tmp, t_cmd *cmd, int *j)
{
	int		size;

	size = 0;
	while (revar)
	{
		if (!revar->name && !revar->data)
			break ;
		if (ft_strcmp(revar->name, tmp) == 0)
			while (revar->data[size])
				cmd->output[(*j)++] = revar->data[size++];
		revar = revar->next;
	}
}

void	dcote_fill_dollar(t_cmd *cmd, t_lists *revar, int *i, int *j)
{
	int		size;
	int		save;
	char	*tmp;

	(*i)++;
	save = *i;
	while (cmd->input[*i] && ((cmd->input[*i] > 47 && cmd->input[*i] < 58)
		|| (cmd->input[*i] > 64 && cmd->input[*i] < 91)
		|| (cmd->input[*i] > 96 && cmd->input[*i] < 123)))
		(*i)++;
	if (!(tmp = (char*)malloc(sizeof(char) * (*i - save) + 1)))
		return ;
	size = 0;
	while (save < *i)
		tmp[size++] = cmd->input[save++];
	tmp[size] = '\0';
	dcote_fill_dollar2(revar, tmp, cmd, j);
	ft_free(tmp);
}
