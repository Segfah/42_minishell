/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redi_flag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:54:13 by corozco           #+#    #+#             */
/*   Updated: 2020/11/19 14:47:49 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_redi_s_error(char **cmd, t_temp *tmp, int i)
{
	if (search_error_redi1(cmd[i]) == -3)
	{
		ft_fprintf(2, "1minishell: syntax error near unexpected token `>'\n");
		return (tmp->flag[1] = -1);
	}
	if (search_error_redi1(cmd[i]) < -3)
	{
		ft_fprintf(2, "2minishell: syntax error near unexpected token `>>'\n");
		return (tmp->flag[1] = -1);
	}
	if (search_error_redi2(cmd[i]) == -1)
	{
		ft_fprintf(2, "3minishell: syntax error near unexpected token `<'\n");
		return (tmp->flag[1] = -1);
	}
	return (0);
}

static int		check_redi_d_error(char **cmd, t_temp *tmp, int i)
{
	if (cmd[i + 1])
	{
		!ft_strcmp(cmd[i + 1], " ") ? i++ : i;
		if (cmd[i + 1] && is_redi(cmd[i + 1]))
		{
			ft_fprintf(2, "minishell: syntax error near unexpected token `%s'\n"
				, cmd[i + 1]);
			return (tmp->flag[1] = -1);
		}
	}
	else
	{
		ft_fprintf(2, "%s syntax error near unexpected token `newline'\n"
			, "minishell:");
		return (tmp->flag[1] = -1);
	}
	return (0);
}

int				check_redi_flag(char **cmd, t_temp *tmp)
{
	int			i;

	tmp->fd = 0;
	tmp->fdi = 0;
	i = 0;
	while (cmd[i])
	{
		if (check_redi_s_error(cmd, tmp, i) != 0)
			return (-1);
		if (is_redi(cmd[i]))
		{
			if (check_redi_d_error(cmd, tmp, i) != 0)
				return (-1);
		}
		(cmd[i] != NULL) ? i++ : i;
	}
	return (0);
}
