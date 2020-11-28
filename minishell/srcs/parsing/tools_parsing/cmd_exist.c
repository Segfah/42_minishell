/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exist.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:22:27 by corozco           #+#    #+#             */
/*   Updated: 2020/11/22 19:06:05 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**build_cmd(t_temp *tmp, char *cmd)
{
	int			a;
	char		*path;
	char		**tabpath;
	char		*temp;

	a = -1;
	if (search_env("PATH", tmp, 0, &path) == -1)
		return (NULL);
	if (!(tabpath = ft_split(path, ':')))
		return (NULL);
	while (tabpath[++a] != NULL)
	{
		temp = tabpath[a];
		if (!(tabpath[a] = ft_strjoin(tabpath[a], "/")))
			return (NULL);
		ft_free(temp);
		temp = tabpath[a];
		if (!(tabpath[a] = ft_strjoin(tabpath[a], cmd)))
			return (NULL);
		ft_free(temp);
	}
	ft_free(path);
	return (tabpath);
}

static int		cmd_is_here(char **path)
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

/*
** si algo falla, era
**	if (flag)
**		return (flag);
**	if (!flag && !search_env("PATH", tmp, 1, NULL))
**		return (flag);
** y
**	if ((tmp->status = cmd_is_here(tmp->tabpath)) == -1)
** si el flag deja de servir cambiar el !(flag = 0) por un flag = 0
** despues del return (-2);
*/

int				cmd_exist(char *cmd, t_temp *tmp, int flag)
{
	if (!cmd)
		return (-2);
	flag = !ft_strcmp(cmd, "exit") ? 1 : flag;
	flag = !ft_strcmp(cmd, "[") ? 10 : flag;
	flag = !ft_strcmp(cmd, ".") ? 11 : flag;
	flag = !ft_strcmp(cmd, "cd") ? 2 : flag;
	flag = !ft_strcmp(cmd, "env") ? 3 : flag;
	flag = !ft_strcmp(cmd, "pwd") ? 4 : flag;
	flag = !ft_strcmp(cmd, "nani") ? 5 : flag;
	flag = !ft_strcmp(cmd, "export") ? 6 : flag;
	flag = !ft_strcmp(cmd, "unset") ? 7 : flag;
	flag = !ft_strcmp(cmd, "echo") ? 8 : flag;
	if (!ft_strcmp(cmd, ".."))
		return (0);
	if (!ft_strncmp(cmd, "./", 2) || !ft_strncmp(cmd, "/", 1)
		|| !ft_strncmp(cmd, "..", 1))
		flag = 9;
	if (flag || (!flag && !search_env("PATH", tmp, 1, NULL)))
		return (flag);
	if (!(tmp->tabpath = build_cmd(tmp, cmd)))
		return (-1);
	if ((tmp->status = cmd_is_here(tmp->tabpath)) == -1 || tmp->status == 0)
		return (0);
	return (9);
}
