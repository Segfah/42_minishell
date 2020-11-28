/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redi_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:54:13 by corozco           #+#    #+#             */
/*   Updated: 2020/11/25 17:42:03 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			search_error_redi1(char *tmp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (tmp[i] == '>')
			j++;
		i++;
	}
	if (j > 2)
		return (-j);
	return (i);
}

int			search_error_redi2(char *tmp)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (tmp[i])
	{
		if (tmp[i] == '<')
			j++;
		i++;
	}
	if (j > 1)
		return (-1);
	return (i);
}

int			is_pipe(char *str)
{
	return (!(ft_strcmp("|", str)));
}

int			check_redi_2(char **cmd, int key, int i)
{
	while (cmd[i])
	{
		if (search_error_redi1(cmd[i]) == -3)
			return (key ? -1 : i);
		if (search_error_redi1(cmd[i]) < -3)
			return (key ? -2 : i);
		if (search_error_redi2(cmd[i]) == -1)
			return (key ? -3 : i);
		if (is_redi(cmd[i]))
		{
			if (cmd[i + 1])
			{
				!ft_strcmp(cmd[i + 1], " ") ? i++ : i;
				if (cmd[i + 1] && is_redi(cmd[i + 1]))
					return (key ? -4 : i);
				if (cmd[i + 1] && is_pipe(cmd[i + 1]))
					return (-35);
			}
			else
				return (key ? -5 : i);
		}
		(cmd[i] != NULL) ? i++ : i;
	}
	return (i);
}
