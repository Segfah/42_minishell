/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dcote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 16:21:39 by lryst             #+#    #+#             */
/*   Updated: 2020/11/25 11:47:29 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	dcote_slash_dollar(int save, t_cmd *cmd, int *i, int *j)
{
	int start;

	start = 0;
	if ((save % 2) == 1)
	{
		while (start++ < ((save / 2)))
			cmd->output[(*j)++] = '\\';
		cmd->output[(*j)++] = cmd->input[(*i)++];
	}
	else
		while (start++ < (save / 2))
			cmd->output[(*j)++] = '\\';
}
 */
void	dcote_fill_slash(t_cmd *cmd, int *i, int *j)
{
	int save;
	int size;

	save = 0;
	size = 0;
	printf("B (dcote_fill_slash)char input[%d] = [%c --- char output[%d] = [%c]\n", *i, cmd->input[*i], *j, cmd->output[*j]);
	while (cmd->input[*i] && cmd->input[*i] == '\\')
	{
		save++;
		(*i)++;
	}
	while (size++ < (save / 2))
		cmd->output[(*j)++] = '\\';
	if (save % 2 == 1)
    {
        if (cmd->input[*i] && (cmd->input[*i] == '"' || cmd->input[*i] == '\'' || cmd->input[*i] == '$'))
            cmd->output[(*j)++] = cmd->input[(*i)++];
		printf("A (dcote_fill_slash)char input[%d] = [%c --- char output[%d] = [%c]\n", *i, cmd->input[*i], *j - 1, cmd->output[*j - 1]);
		/* if (save == 1)
		{
			(*size)++;
			//printf("A1 (dcote_count_slash)char input[%d] = [%c] ----- size = [%d]\n", *i, cmd->input[*i], *size);
			return ;
		} */
    }
	/* if (cmd->input[*i] == '$')
		dcote_slash_dollar(save, cmd, i, j);
	else if (save == 1 && cmd->input[*i] != '"' && cmd->input[*i] != '\'')
		cmd->output[(*j)++] = '\\'; */
	else
		while (size++ < (save / 2))
			cmd->output[(*j)++] = '\\';
}

void    dcote_count_slash(t_cmd *cmd, int *i, int *size)
{
    int save;
    save = 0;
	printf("B (dcote_count_slash)char input[%d] = [%c] ----- size = [%d]\n", *i, cmd->input[*i], *size);
    while (cmd->input[*i] && cmd->input[*i] == '\\')
    {
        save++;
        (*i)++;
    }
    if (save % 2 == 1)
    {
        if (cmd->input[*i] && (cmd->input[*i] == '"' || cmd->input[*i] == '\'' || cmd->input[*i] == '$'))
            (*i)++;
		if (save == 1)
		{
			(*size)++;
			printf("A1 (dcote_count_slash)char input[%d] = [%c] ----- size = [%d]\n", *i, cmd->input[*i], *size);
			return ;
		}
    }
    (*size) = (*size) + (save / 2);
	printf("A2 (dcote_count_slash)char input[%d] = [%c] ----- size = [%d]\n", *i, cmd->input[*i], *size);

}

void	dcote_fill_dollar(t_cmd *cmd, t_lists *revar, int *i, int *j)
{
	int		size;
	int		save;
	char	*tmp;

	(*i)++;
	save = *i;
	printf("B (dcote_fill_dollar)char input[%d] = [%c --- char output[%d] = [%c]\n", *i, cmd->input[*i], *j, cmd->output[*j]);
	while (cmd->input[*i] && ((cmd->input[*i] > 47 && cmd->input[*i] < 58) ||
	(cmd->input[*i] > 64 && cmd->input[*i] < 91) || (cmd->input[*i] > 96 &&
	cmd->input[*i] < 123)))
		(*i)++;
	if (!(tmp = (char*)malloc(sizeof(char) * (*i - save) + 1)))
		return ;
	size = 0;
	while (save < *i)
		tmp[size++] = cmd->input[save++];
	tmp[size] = '\0';
	size = 0;
	while (revar)
	{
		if (!revar->name && !revar->data)
			break ;
		if (ft_strcmp(revar->name, tmp) == 0)
		{
			while (revar->data[size])
				cmd->output[(*j)++] = revar->data[size++];
		}
		revar = revar->next;
	}
	printf("A (dcote_fill_dollar)char input[%d] = [%c --- char output[%d] = [%c]\n", *i, cmd->input[*i], *j, cmd->output[*j]);
	ft_free(tmp);
}

void	dcote_count_dollar(t_cmd *cmd, t_lists *var, int *i, int *size)
{
	int		save;
	char	*tmp;
	int		j;

	j = 0;
	(*i)++;
	save = *i;
	while (cmd->input[*i] && ((cmd->input[*i] > 47 && cmd->input[*i] < 58) ||
	(cmd->input[*i] > 64 && cmd->input[*i] < 91) || (cmd->input[*i] > 96 &&
	cmd->input[*i] < 123)))
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
	if (cmd->input[*i] && ((cmd->input[*i + 1] > 47 &&
		cmd->input[*i + 1] < 58) || (cmd->input[*i + 1] > 64 &&
		cmd->input[*i + 1] < 91) || (cmd->input[*i + 1] > 96 &&
		cmd->input[*i + 1] < 123)))
	{
		printf("B (before_count_dollar)char input[%d] = [%c] ----- size = [%d]\n", *i, cmd->input[*i], *size);
		dcote_count_dollar(cmd, var, i, size);
		printf("A (before_count_dollar)char input[%d] = [%c] ----- size = [%d]\n", *i, cmd->input[*i], *size);
	}
	else
	{
		(*size)++;
		(*i)++;
	}
}
