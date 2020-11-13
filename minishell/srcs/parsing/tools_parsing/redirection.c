/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:54:13 by corozco           #+#    #+#             */
/*   Updated: 2020/10/22 16:54:15 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				check_redi(char **cmd, t_temp *tmp)
{
	int			i;

	tmp->fd = 0;
	tmp->fdi = 0;
	i = -1;
	while (cmd[++i])
	{
		if (is_redi(cmd[i]))
		{
			if (cmd[i + 1])
			{
				if (is_redi(cmd[i + 1]))
				{
					printf("minishell: syntax error near unexpected token `%s'\n", cmd[i]);
					return (tmp->flag[1] = -1);
				}
			}
			else
			{
				printf("minishell: syntax error near unexpected token `newline'\n");
				return (tmp->flag[1] = -1);
			}
		}
	}
	i = -1;
	while (cmd[++i])
	{
//		if (!(ft_strcmp(">", cmd[i]))) // y que en la lista encadenada no sea ">" con guimes
		if (!(ft_strcmp(">", cmd[i])))
		{
			tmp->flag[1] = 1;
			if (tmp->flag[2] != -1 && simple_redi(cmd[i + 1], tmp) == -1)
				return (tmp->flag[1] = -1);
		}
		else if (tmp->flag[2] != -1 && !(ft_strcmp(">>", cmd[i])))
		{
			tmp->flag[1] = 1;
			if (double_redi(cmd[i + 1], tmp) == -1)
				return (tmp->flag[1] = -1);
		}
		else if (!(ft_strcmp("<", cmd[i])))
		{
			tmp->flag[2] = 1;
			if (contre_redi(cmd[i + 1], tmp) == -1)
				return (tmp->flag[2] = -1);
		}
	}
	return (0);
}

void			skip_redi(char **cmd)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (!(ft_strcmp(">", cmd[i])) || !(ft_strcmp(">>", cmd[i])) || !(ft_strcmp("<", cmd[i])))
		{
			ft_free(cmd[i]);
			ft_free(cmd[i + 1]);
			i = i + 2;
		}
		else
			cmd[j++] = cmd[i++];
	}
	cmd[j] = 0;
}