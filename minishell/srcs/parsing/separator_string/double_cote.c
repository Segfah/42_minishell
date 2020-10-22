/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_cote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 14:06:11 by lryst             #+#    #+#             */
/*   Updated: 2020/10/15 17:53:00 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_cote_cmd_3(t_cmd *cmd, t_lists *revar, int *i, int *j)
{
	if (cmd->input[*i] == '$')
	{
		if (cmd->input[*i] && ((cmd->input[*i + 1] > 47 &&
		cmd->input[*i + 1] < 58) ||
		(cmd->input[*i + 1] > 64 && cmd->input[*i + 1] < 91) ||
		(cmd->input[*i + 1] > 96 && cmd->input[*i + 1] < 123)))
			double_cote_fill_dollar(cmd, revar, i, j);
		else
			cmd->output[(*j)++] = cmd->input[(*i)++];
	}
	if (cmd->input[*i] == '\\')
		double_cote_fill_slash(cmd, i, j);
}

void	double_cote_cmd_2(t_cmd *cmd, t_lists *revar, int size)
{
	int i;
	int j;
	int len;

	if (!(cmd->output = (char*)malloc(sizeof(char) * size + 1)))
		return ;
	size = 0;
	i = 1;
	j = 0;
	len = ft_strlen(cmd->input) - 1;
	while (cmd->input[i] && i < len)
	{
		double_cote_cmd_3(cmd, revar, &i, &j);
		if (cmd->input[i] && i < len && cmd->input[i] != '\\' &&
			cmd->input[i] != '$')
			cmd->output[j++] = cmd->input[i];
		i++;
	}
	cmd->output[j] = '\0';
}

void	double_cote_cmd(t_cmd *cmd, t_lists *var)
{
	int		i;
	int		size;
	int		len;
	t_lists	*revar;

	i = 1;
	size = 0;
	revar = var;
	len = ft_strlen(cmd->input) - 1;
	while (cmd->input[i] && i < len)
	{
		if (cmd->input[i] == '$')
			before_count_dollar(cmd, var, &i, &size);
		if (cmd->input[i] == '\\')
			double_cote_count_slash(cmd, &i, &size);
		if (cmd->input[i] != '\\' && cmd->input[i] != '$')
			size++;
		i++;
	}
	double_cote_cmd_2(cmd, revar, size);
}