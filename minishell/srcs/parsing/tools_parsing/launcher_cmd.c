/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launcher_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:11:19 by lryst             #+#    #+#             */
/*   Updated: 2020/11/26 01:10:49 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		gestion_missing(t_temp *tmp)
{
	int			i;

	i = -1;
	while (tmp->strcmd[++i])
	{
		if (!ft_strcmp("]", tmp->strcmd[i]))
			return ;
	}
	ft_fprintf(2, "minishell: [: missing `]'\n");
}

static void		launcher_cmd2(char *tabcmd, t_temp *tmp, int j)
{
	if (j == 10)
		gestion_missing(tmp);
	else if (j == 7)
		gestion_unset(tmp);
	else if (j == 8)
		gestion_echo(tmp);
	else if (j == 9 && command_bin(tmp->strcmd, tmp) == 0)
		return ;
	else if (j == 11)
		point_filename(tmp->strcmd);
	else
		cmd_not_found(tabcmd, tmp);
}

void			launcher_cmd(char *tabcmd, t_temp *tmp, int j, int key)
{
	if (tabcmd[0] == 0 || j == -2 || tmp->flag[1] == -1 || tmp->flag[2] == -1)
		return ;
	else if (j == 1)
		gestion_exit(tmp->strcmd, tmp, key);
	else if (j == 2)
		gestion_cd(tmp->strcmd, tmp);
	else if (j == 3)
		gestion_env(tmp->strcmd, tmp);
	else if (j == 4)
		gestion_pwd(tmp->strcmd, tmp);
	else if (j == 5)
		gestion_nani(tmp->strcmd);
	else if (j == 6)
		gestion_export(tmp, 0);
	else
		launcher_cmd2(tabcmd, tmp, j);
}
