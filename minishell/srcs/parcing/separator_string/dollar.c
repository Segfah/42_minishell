/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:57:34 by lryst             #+#    #+#             */
/*   Updated: 2020/10/01 22:57:36 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	replace_isspace(l_cmd *cmd, int *i, int *j, char ascii)
{
	cmd->output[*i] = ascii;
	(*i)++;
	*j = *j + 2;
}

void	dollar_cmd(l_cmd *cmd, t_lists *var)
{
	int i;
	int j;
	char *save;

	i = 1;
	j = 0;
	
	if (ft_strcmp(cmd->input, "$?") == 0)
	{
		cmd->output = ft_itoa(g_ret);
		return ;
	}
	if (!(save = (char*)malloc(sizeof(char) * ft_strlen(cmd->input))))
		return ;
	while (cmd->input[i])
		save[j++] = cmd->input[i++];
	save[j] = '\0';
	j = 0;
	i = 0;
	if (save[j] == '\'')
	{
		j++;
		if ((cmd->output = (char*)malloc(sizeof(char) * ft_strlen(save))))
		{
			while (save[j] && save[j] != '\'')
			{
				if (save[j] == '\\' && save[j + 1] == 't')
					replace_isspace(cmd, &i, &j, '\t');
				else if (save[j] == '\\' && save[j + 1] == 'n')
					replace_isspace(cmd, &i, &j, '\n');
				else if (save[j] == '\\' && save[j + 1] == 'v')
					replace_isspace(cmd, &i, &j, '\v');
				else if (save[j] == '\\' && save[j + 1] == 'f')
					replace_isspace(cmd, &i, &j, '\f');
				else if (save[j] == '\\' && save[j + 1] == 'r')
					replace_isspace(cmd, &i, &j, '\r');
				else
					cmd->output[i++] = save[j++];
			}
		}
		return ;
	}
	if (ft_strcmp(cmd->input, "$\0") == 0)
	{
		cmd->output = ft_strdup(cmd->input);
		return ;
	}
	while (var)
	{
		if (ft_strcmp(var->name, save) == 0)
		{
			cmd->output = ft_strdup(var->data);
			ft_free(save);
			return ;
		}
		var = var->next;
	}
	ft_free(save);
	cmd->output = NULL;
}
