/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_tab3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 09:52:45 by lryst             #+#    #+#             */
/*   Updated: 2020/11/23 09:54:08 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				len_error_pipe(t_cmd *tmp, int *pipe)
{
	if (search_error_pipe(tmp) == -1)
		return (-1);
	if (!ft_strcmp(tmp->input, "|") && !tmp->next)
		return (-3);
	else if (!ft_strcmp(tmp->input, "|") &&
		!ft_strcmp(tmp->next->input, " ") && !tmp->next->next)
		return (-1);
	else if (!ft_strcmp(tmp->input, "|") && !ft_strcmp(tmp->next->input, " ")
		&& !ft_strcmp(tmp->next->next->input, "|"))
		return (-2);
	else if (!ft_strcmp(tmp->input, "|") && ft_strcmp(tmp->next->input, " ")
		&& !ft_strcmp(tmp->next->input, "|"))
		return (-2);
	else if (!ft_strcmp(tmp->input, "|"))
		(*pipe)++;
	return (0);
}

int				len_split3d(t_cmd *cmd)
{
	int			pipe;
	t_cmd		*tmp;
	int			ret;

	tmp = cmd;
	pipe = 0;
	ret = 0;
	if (tmp && !ft_strcmp(tmp->input, "|"))
		return (-1);
	while (tmp)
	{
		if ((ret = len_error_pipe(tmp, &pipe)) != 0)
			return (ret);
		tmp = tmp->next;
	}
	if (pipe == 0)
		return (0);
	return (pipe + 1);
}

int				len_tabsplit3d(t_cmd *cmd)
{
	t_cmd		*tmp;
	int			ret;

	ret = 0;
	tmp = cmd;
	while (tmp)
	{
		if (!ft_strcmp(tmp->input, "|"))
			return (ret);
		ret++;
		tmp = tmp->next;
	}
	return (ret);
}
