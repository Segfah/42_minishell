/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_command_bin.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 10:59:48 by lryst             #+#    #+#             */
/*   Updated: 2020/11/19 16:52:19 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void			is_directory(char **tab_env, char **tab)
{
	struct stat sb;

	stat(tab[0], &sb);
	if (sb.st_mode & S_IFDIR)
	{
		ft_fprintf(2, "minishell: %s: is a directory\n", tab[0]);
		exit(33);
	}
	if (execve(tab[0], tab, tab_env) == -1)
	{
		ft_fprintf(2, "minishell: %s: %s\n", tab[0], strerror(errno));
		errno == 2 ? ft_nb_exit(34) : ft_nb_exit(33);
	}
	exit(0);
}

int				command_bin_2(char **tab_env, char **tab, t_temp *tmp)
{
	(tmp->flag[2] == 1) ? dup2(tmp->fdi, 0) : 0;
	(tmp->flag[1] == 1) ? dup2(tmp->fd, 1) : 0;
	if (!ft_strcmp(tab[0], "/") || !ft_strcmp(tab[0], "./"))
	{
		ft_fprintf(2, "minishell: %s: is a directory\n", tab[0]);
		exit(33);
	}
	if (!tmp->tabpath)
		is_directory(tab_env, tab);
	else if (execve(tmp->tabpath[tmp->status], tab, tab_env) == -1)
		exit(1);
	exit(0);
}

void			command_bin_3(t_temp *tmp)
{
	if (WEXITSTATUS(tmp->status) == 0)
		g_ret = 0;
	if (WEXITSTATUS(tmp->status) == 33)
		g_ret = 126;
	if (WEXITSTATUS(tmp->status) == 34)
		g_ret = 127;
}
