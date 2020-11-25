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

int				command_bin_2(char **tab_env, char **tab, t_temp *tmp, int key)
{
	(tmp->flag[2] == 1) ? dup2(tmp->fdi, 0) : 0;
	(tmp->flag[1] == 1) ? dup2(tmp->fd, 1) : 0;
	if (!ft_strcmp(tab[0], "/") || !ft_strcmp(tab[0], "./"))
	{
		g_ret = 126;
		if (key == 1)
			exit(16);
		ft_printf("minishell: /: is a directory\n");
		exit(33);
	}
	if (!tmp->tabpath)
	{
		struct stat sb;
		stat(tab[0], &sb);
/* 		if (stat(tab[0], &sb) == -1)
		{
			perror("statssss");
			exit(0);
		} */
		if (sb.st_mode & S_IFDIR)
		{
			if (key == 1)
				exit(16);
			ft_printf("minishell: %s: is a directory\n", tab[0]);
			exit(33);
		}
		if (execve(tab[0], tab, tab_env) == -1)
		{
			if (key == 1)
				exit(errno);
			ft_printf("minishell: %s: %s\n", tab[0], strerror(errno));
			exit(1);
		}
		exit(0);
	}
	else if (execve(tmp->tabpath[tmp->status], tab, tab_env) == -1)
		exit(1);
	exit(0);
}

void			command_bin_3(t_temp *tmp)
{
	if (WEXITSTATUS(tmp->status) == 0)
		g_ret = 0;
	if (WEXITSTATUS(tmp->status) == 16)
	{
		g_ret = 126;
		exit(16);
	}
	if (WEXITSTATUS(tmp->status) == 33)
		g_ret = 126;
	if (WEXITSTATUS(tmp->status) == 13)
		exit(13);
	if (WEXITSTATUS(tmp->status) == 2)
		exit(2);
}
