/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 14:07:09 by lryst             #+#    #+#             */
/*   Updated: 2020/10/03 20:42:31 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	single_cote_cmd(t_cmd *cmd)
{
	int i;
	int j;
	int len;

	i = 1;
	j = 0;
	len = ft_strlen(cmd->input) - 1;
	if (!(cmd->output = (char*)malloc(sizeof(char) * len)))
		return ;
	while (cmd->input[i] && i < len)
		cmd->output[j++] = cmd->input[i++];
	cmd->output[j] = '\0';
}
