/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:54:13 by corozco           #+#    #+#             */
/*   Updated: 2020/11/25 18:49:54 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				search_error_pipe(t_cmd *tmp)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (tmp->input[i])
	{
		if (tmp->input[i] == '|')
			j++;
		i++;
	}
	if (j > 1)
		return (-1);
	return (i);
}

int				tab2_3d2(int key, t_temp *tmp, int *k, int *i)
{
	if (key >= 0)
	{
		if (!(tmp->outpipe[*i] = (char**)malloc(sizeof(char *) * key + 1)))
			return (-1);
		if (!(tmp->inpipe[*i] = (char**)malloc(sizeof(char *) * key + 1)))
			return (-1);
		if (!(tmp->cpypipe[*i] = (char**)malloc(sizeof(char *) * key + 1)))
			return (-1);
	}
	if (key == -2)
	{
		tmp->outpipe[*i][*k] = NULL;
		tmp->inpipe[*i][*k] = NULL;
		tmp->cpypipe[(*i)++][*k] = NULL;
	}
	if (key == -1)
	{
		tmp->outpipe[*i] = NULL;
		tmp->inpipe[*i] = NULL;
		tmp->cpypipe[*i] = NULL;
	}
	return (0);
}

int				tab2_3d(t_cmd *cmd, t_temp *tmp, int i)
{
	t_cmd		*tmpo;
	int			k;
	int			len;

	tmpo = cmd;
	while (tmpo)
	{
		k = -1;
		len = len_tabsplit3d(tmpo);
		if (tab2_3d2(len, tmp, &k, &i) == -1)
			return (-1);
		while (++k < len)
		{
			if (!(tmp->inpipe[i][k] = ft_strdup(tmpo->input))
				|| !(tmp->outpipe[i][k] = ft_strdup(tmpo->output))
				|| !(tmp->cpypipe[i][k] = ft_strdup(tmpo->input)))
				return (-1);
			(tmpo->next) ? tmpo = tmpo->next : 0;
		}
		tab2_3d2(-2, tmp, &k, &i);
		tmpo = tmpo->next;
	}
	tab2_3d2(-1, tmp, &k, &i);
	return (0);
}

int				print_error(int ret)
{
	if (ret == -1 || ret == -2)
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
	if (ret == -3)
		return (-3);
	return (-1);
}

int				split3d(t_cmd *cmd, t_temp *tmp)
{
	int			ret;

	if ((ret = len_split3d(cmd)) == 0)
		return (0);
	if (ret < 0)
	{
		return (print_error(ret));
	}
	tmp->nb_pipes = ret - 1;
	if (!(tmp->outpipe = (char***)malloc(sizeof(char**) * ret + 1)))
		return (-1);
	if (!(tmp->inpipe = (char***)malloc(sizeof(char**) * ret + 1)))
		return (-1);
	if (!(tmp->cpypipe = (char***)malloc(sizeof(char**) * ret + 1)))
		return (-1);
	if (tab2_3d(cmd, tmp, 0) == -1)
		return (-1);
	clean_split3d(tmp);
	return (1);
}
