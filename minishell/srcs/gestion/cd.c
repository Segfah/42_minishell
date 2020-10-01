/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 22:10:58 by lryst             #+#    #+#             */
/*   Updated: 2020/10/01 23:09:31 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <errno.h>

void			gestion_cd(char **strcmd, t_temp *tmp)
{
	if (strcmd[1])
	{
		tmp->env = getcwd(NULL, 0);
		if (chdir(strcmd[1]) != 0)
		{
			g_ret = 1;
			ft_printf("cd: %s: %s\n", strerror(errno), strcmd[1]);
		}
		else
		{
			g_ret = 0;
			change_list(tmp->varenv, "OLDPWD", tmp->env);
			free(tmp->env);
			tmp->env = getcwd(NULL, 0);
			change_list(tmp->varenv, "PWD", tmp->env);
		}
		free(tmp->env);
	}
}
