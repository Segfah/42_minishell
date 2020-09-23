/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 14:08:13 by lryst             #+#    #+#             */
/*   Updated: 2020/09/14 14:08:54 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	slash_cmd(l_cmd *cmd)
{
	int i;
	int count;

	i = 1;
	count = 0;
	if (cmd->input[i] != '\0' && cmd->input[i] != '\\')
	{
		if (!(cmd->output = (char*)malloc(sizeof(char) * ft_strlen(cmd->input))))
			return ;
		while (cmd->input[i])
			cmd->output[count++] = cmd->input[i++];
	}
	else
	{
		i = 0;
		while (cmd->input[i] && cmd->input[i++] == '\\')
			count++;
		if(!(cmd->output = (char*)malloc(sizeof(char) * (ft_strlen(cmd->input) / 2) + 1)))
			return;
		count = count / 2;
		i = 0;
		while (i < count)
			cmd->output[i++] = '\\';
	}
	cmd->output[i] = '\0';
}
