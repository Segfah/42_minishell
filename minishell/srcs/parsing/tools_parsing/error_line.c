/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:54:13 by corozco           #+#    #+#             */
/*   Updated: 2020/11/19 14:47:49 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		print_error_redi(char *str, int key)
{
	if (key == -1)
		ft_fprintf(2, "minishell: syntax error near unexpected token `>'\n");
	if (key == -2)
		ft_fprintf(2, "minishell: syntax error near unexpected token `>>'\n");
	if (key == -3)
		ft_fprintf(2, "minishell: syntax error near unexpected token `<'\n");
	if (key == -4)
		ft_fprintf(2, "minishell: syntax error near unexpected token `%s'\n"
			, str);
	if (key == -5)
		write(2, "minishell: syntax error near unexpected token `newline'\n"
			, 56);
	if (key == -35)
		ft_fprintf(2, "minishell: syntax error near unexpected token `|'\n");
}

static int		redi_error(t_cmd *cmd, t_temp *tmp)
{
	int			ret;

	ret = (cmd) ? llist_astring(cmd, tmp) : 0;
	if (ret == -1)
	{
		free_cmd(cmd);
		general_free(tmp);
	}
	if (tmp->strcmdin && (ret = check_redi_2(tmp->strcmdin, 1, 0)) < 0)
	{
		print_error_redi(tmp->strcmd[check_redi_2(tmp->strcmd, 0, 0) + 1], ret);
		ft_free_double_tab(tmp->strcmd);
		ft_free_double_tab(tmp->strcmdin);
		ft_free_double_tab(tmp->cpytab);
		(cmd != NULL) ? free_cmd(cmd) : 0;
		g_ret = 258;
		return (-1);
	}
	return (0);
}

static int		error_multi(t_cmd *cmd, t_temp *tmp)
{
	ft_fprintf(2, "error multi\n");
	ft_free_double_tab(tmp->strcmd);
	ft_free_double_tab(tmp->strcmdin);
	ft_free_double_tab(tmp->cpytab);
	(cmd != NULL) ? free_cmd(cmd) : 0;
	g_ret = 258;
	return (-1);
}

static int		pipe_error(t_cmd *cmd, t_temp *tmp)
{
	int		ret;

	ret = 0;
	if ((ret = len_split3d(cmd)) < 0)
	{
		if (ret != -3 && (g_ret = 258))
		{
			ft_free_double_tab(tmp->strcmd);
			(cmd != NULL) ? free_cmd(cmd) : 0;
			print_error(ret);
			g_ret = 258;
			return (-1);
		}
	}
	return (ret);
}

int				error_line(char **tabcmd, t_temp *tmp, int i)
{
	t_cmd		*cmd;
	int			ret;

	while (tabcmd[++i])
	{
		initialize(tmp, &ret);
		cmd = NULL;
		separator_string(&cmd, tabcmd[i], tmp);
		if ((ret = pipe_error(cmd, tmp)) == -1)
			return (-1);
		if (redi_error(cmd, tmp) == -1)
			return (-1);
		if (ret == -3)
			return (error_multi(cmd, tmp));
		ft_free_double_tab(tmp->strcmd);
		ft_free_double_tab(tmp->strcmdin);
		ft_free_double_tab(tmp->cpytab);
		(cmd != NULL) ? free_cmd(cmd) : 0;
	}
	return (0);
}
