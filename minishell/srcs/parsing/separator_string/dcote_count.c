/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dcote_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 16:21:39 by lryst             #+#    #+#             */
/*   Updated: 2020/12/01 10:23:23 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dcote_count_slash(t_cmd *cmd, int *i, int *size)
{
	int save;

	save = 0;
	while (cmd->input[*i] && cmd->input[*i] == '\\')
	{
		save++;
		(*i)++;
	}
	if (save % 2 == 1)
	{
		if (cmd->input[*i] && (cmd->input[*i] == '"' || cmd->input[*i] == '$'))
			(*i)++;
		if (save == 1)
		{
			(*size)++;
			return ;
		}
	}
	(*size) = (*size) + (save / 2);
}

void	dcote_count_dollar(t_cmd *cmd, t_lists *var, int *i, int *size)
{
	int		save;
	char	*tmp;
	int		j;

	j = 0;
	(*i)++;
	save = *i;
	while (cmd->input[*i] && ((cmd->input[*i] > 47 && cmd->input[*i] < 58)
		|| (cmd->input[*i] > 64 && cmd->input[*i] < 91)
		|| (cmd->input[*i] > 96 && cmd->input[*i] < 123)))
		(*i)++;
	if (!(tmp = (char*)malloc(sizeof(char) * (*i - save) + 1)))
		return ;
	while (save < *i)
		tmp[j++] = cmd->input[save++];
	tmp[j] = '\0';
	while (var)
	{
		if (!var->name && !var->data)
			break ;
		if (ft_strcmp(var->name, tmp) == 0)
			(*size) = (*size) + ft_strlen(var->data);
		var = var->next;
	}
	ft_free(tmp);
}

void	before_count_dollar(t_cmd *cmd, t_lists *var, int *i, int *size)
{
	if (cmd->input[*i] && ((cmd->input[*i + 1] > 47 && cmd->input[*i + 1] < 58)
	|| (cmd->input[*i + 1] > 64 && cmd->input[*i + 1] < 91)
	|| (cmd->input[*i + 1] > 96 && cmd->input[*i + 1] < 123)))
	{
		dcote_count_dollar(cmd, var, i, size);
	}
	else
	{
		(*size)++;
		(*i)++;
	}
}
