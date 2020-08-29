/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:00:48 by lryst             #+#    #+#             */
/*   Updated: 2020/08/30 01:43:34 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static char		**build_cmd(t_temp *tmp, char *cmd, int *a)
{
	char		*path;
	char		**tabpath;
	char		*temp;

	if (search_env("PATH", tmp, 0, &path) == -1)
		return (NULL);
	if (!(tabpath = ft_split(path, ':')))
		return (NULL);
	while (tabpath[++(*a)] != NULL)
	{
		temp = tabpath[*a];
		if (!(tabpath[*a] = ft_strjoin(tabpath[*a], "/")))
			return (NULL);
		free(temp);
		temp = tabpath[*a];
		if (!(tabpath[*a] = ft_strjoin(tabpath[*a], cmd)))
			return (NULL);
		free(temp);
	}
	free(path);
	return (tabpath);
}


int				cmd_is_here(char **path)
{
	int			i;
	struct stat	stats;

	i = -1;
	while (path[++i])
	{
		if (stat(path[i], &stats) == 0)
			return (i);
	}
	return (-1);
}

int				command_bin(char **tab, t_temp *tmp)
{
	char		*new_env[] = {NULL};
	pid_t		f;
//	pid_t		w;
	int			status;
	char		**tabpath;
	int			i;
	int			s_bin;

	i = -1;
	if ((search_env("PATH", tmp, 1, NULL) == 0)
		|| !(tabpath = build_cmd(tmp, tab[0], &i)))
		return (-1);
	if ((s_bin =cmd_is_here(tabpath)) == -1)
		return (-1);
	f = fork();
	if (f == 0)
	{
		if (execve(tabpath[s_bin], tab, new_env) == -1)
			exit(1);
		exit(0);
	}
	if ((f = waitpid(f, &status, WUNTRACED | WCONTINUED)) == -1)
		exit(1);
	ft_free_split(tabpath, i);
	return (0);
}
