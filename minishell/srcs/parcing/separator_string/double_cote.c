/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_cote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 14:06:11 by lryst             #+#    #+#             */
/*   Updated: 2020/10/13 16:33:01 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		double_cote_size_var(t_cmd *cmd, int save, int *i, t_lists *var)
{
	char *tmp;
	int j;
	int size;

	j = 0;
	if (!(tmp = (char*)malloc(sizeof(char) * (*i - save) + 1)))
		return (-1);
	while (save < *i)
		tmp[j++] = cmd->input[save++];
	tmp[j] = '\0';
	while (var)
	{
		if (ft_strcmp(var->name, tmp) == 0)
			size = size + ft_strlen(var->data);
		var = var->next;
	}
	ft_free(tmp);
	return (size);
}

void	double_cote_count_dollar(t_cmd *cmd, int *i, int *size, t_lists *var)
{
	int save;

	if (cmd->input[*i] && ((cmd->input[*i + 1] > 47 && cmd->input[*i + 1] < 58)
	|| (cmd->input[*i + 1] > 64 && cmd->input[*i + 1] < 91) ||
	(cmd->input[*i + 1] > 96 && cmd->input[*i + 1] < 123)))
	{
		(*i)++;
		save = *i;
		while (cmd->input[*i] && ((cmd->input[*i] > 47 && cmd->input[*i] < 58)
		|| (cmd->input[*i] > 64 && cmd->input[*i] < 91) ||
		(cmd->input[*i] > 96 && cmd->input[*i] < 123)))
			(*i)++;
		size = size + double_cote_size_var(cmd, save, i, var);
	}
	else
		size++;
	(*i)++;
}

void	double_cote_cmd(t_cmd *cmd, t_lists *var)
{
	int i;
	int j;
	int size;
	int save;
	char *tmp;
	int len;
	t_lists	*revar;

	i = 1;
	j = 0;
	size = 0;
	revar = var;
	len = ft_strlen(cmd->input) - 1;
	while (cmd->input[i] && i < len)
	{
		if (cmd->input[i] == '$')
			double_cote_count_dollar(cmd, &i, &size, var);
		/* {
			if (cmd->input[i] && ((cmd->input[i + 1] > 47 && cmd->input[i + 1] < 58) || (cmd->input[i + 1] > 64 && cmd->input[i + 1] < 91) || (cmd->input[i + 1] > 96 && cmd->input[i + 1] < 123)))
			{
				i++;
				save = i;
				while (cmd->input[i] && ((cmd->input[i] > 47 && cmd->input[i] < 58) || (cmd->input[i] > 64 && cmd->input[i] < 91) || (cmd->input[i] > 96 && cmd->input[i] < 123)))
					i++;
				if (!(tmp = (char*)malloc(sizeof(char) * (i - save) + 1)))
					return ;
				while (save < i)
					tmp[j++] = cmd->input[save++];
				tmp[j] = '\0';
				while (var)
				{
					if (ft_strcmp(var->name, tmp) == 0)
						size = size + ft_strlen(var->data);
					var = var->next;
				}
				ft_free(tmp);
			}
			else
				size++;
			i++;
		} */
		if (cmd->input[i] == '\\')
		{
			save = 0;
			while (cmd->input[i] && cmd->input[i] == '\\')
			{
				save++;
				i++;
			}
			if (save == 1)
				size++;
			else
				size = size + (save / 2);
		}
		if (cmd->input[i] != '\\' && cmd->input[i] != '$')
			size++;
		i++;
	}
	if (!(cmd->output = (char*)malloc(sizeof(char) * size + 1)))
		return ;
	size = 0;
	i = 1;
	j = 0;
	while (cmd->input[i] && i < len)
	{
		if (cmd->input[i] == '$')
		{
			if (cmd->input[i] && ((cmd->input[i + 1] > 47 && cmd->input[i + 1] < 58) || (cmd->input[i + 1] > 64 && cmd->input[i + 1] < 91) || (cmd->input[i + 1] > 96 && cmd->input[i + 1] < 123)))
			{
				i++;
				save = i;
				while (cmd->input[i] && ((cmd->input[i] > 47 && cmd->input[i] < 58) || (cmd->input[i] > 64 && cmd->input[i] < 91) || (cmd->input[i] > 96 && cmd->input[i] < 123)))
					i++;
				if (!(tmp = (char*)malloc(sizeof(char) * (i - save) + 1)))
					return ;
				size = 0;
				while (save < i)
					tmp[size++] = cmd->input[save++];
				tmp[size] = '\0';
				size = 0;
				while (revar)
				{
					if (ft_strcmp(revar->name, tmp) == 0)
						while (revar->data[size])
							cmd->output[j++] = revar->data[size++];
					revar = revar->next;
				}
			}
			else
				cmd->output[j++] = cmd->input[i++];
		}
		if (cmd->input[i] == '\\')
		{
			save = 0;
			size = 0;
			while (cmd->input[i] && cmd->input[i] == '\\')
			{
				save++;
				i++;
			}
			if (save == 1 && cmd->input[i] != '"' && cmd->input[i] != '\'')
				cmd->output[j++] = '\\';
			else
				while (size++ < (save / 2))
					cmd->output[j++] = '\\';
		}
		if (cmd->input[i] && i < len && cmd->input[i] != '\\' && cmd->input[i] != '$')
			cmd->output[j++] = cmd->input[i];
		i++;
	}
	cmd->output[j] = '\0';
}
