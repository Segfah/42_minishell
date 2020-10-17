/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 22:10:58 by lryst             #+#    #+#             */
/*   Updated: 2020/10/17 16:16:07 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <errno.h>

void			gestion_cd(char **strcmd, t_temp *tmp)
{
	char *home;

	home = NULL;
	tmp->env = getcwd(NULL, 0);
	g_ret = 0;
	if (strcmd[1] != NULL)
	{
		if (chdir(strcmd[1]) != 0 && (g_ret = 1))
			ft_printf("cd: %s: %s\n", strerror(errno), strcmd[1]);
	}
	else
	{
		search_env("HOME", tmp, 0, &home);
		if (home)
		{
			if (chdir(home) != 0 && (g_ret = 1))
				ft_printf("cd: %s: %s\n", strerror(errno), home);
		}
		else
			(g_ret = 1) ? write(1, "minishell: cd: HOME not set\n", 28) : 0;
		home ? free(home) : 0;
	}
	!g_ret ? change_list(tmp->varenv, "OLDPWD", tmp->env) : 0;
	free(tmp->env);
	tmp->env = getcwd(NULL, 0);
	change_list(tmp->varenv, "PWD", tmp->env);
	free(tmp->env);
	if (tmp->flag[1])
		close(tmp->fd);
}
/*
void			gestion_cd(char **strcmd, t_temp *tmp)
{
	char *home;

	home = NULL;
	tmp->env = getcwd(NULL, 0);
	g_ret = 0;
	if (strcmd[1] != NULL)
	{
		if (chdir(strcmd[1]) != 0)
		{
			g_ret = 1;
			ft_printf("cd: %s: %s\n", strerror(errno), strcmd[1]);
		}
	}
	else
	{
		search_env("HOME", tmp, 0, &home);
		home ? chdir(home) : chdir(tmp->hnull);
		home ? free(home) : 0;
	}
	change_list(tmp->varenv, "OLDPWD", tmp->env);
	free(tmp->env);
	tmp->env = getcwd(NULL, 0);
	change_list(tmp->varenv, "PWD", tmp->env);
	free(tmp->env);
	if (tmp->flag[1])
		close(tmp->fd);
}
*/
