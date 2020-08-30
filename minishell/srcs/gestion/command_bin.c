/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:00:48 by lryst             #+#    #+#             */
/*   Updated: 2020/08/30 05:13:22 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

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
		free(temp);
		temp = tabpath[a];
		if (!(tabpath[a] = ft_strjoin(tabpath[a], cmd)))
			return (NULL);
		free(temp);
	}
	free(path);
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

int				lists_size(t_lists *lst)
{
	int			i;
	t_lists		*tmp;

	i = 0;
	if (!lst)
		return (i);
	tmp = lst->next;
	while (tmp != NULL)
	{
		if (tmp->data != NULL)
			i++;
		tmp = tmp->next;
	}
	return (++i);
}

char			**c_env(t_lists *list, int size)
{
	char		**tab;
	int			i;
	char		*tempo;
	t_lists		*tmp;

	if (!(tab = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	i = 0;
	tmp = list;
	while (tmp != NULL)
	{
		if (tmp->data != NULL)
		{
			if (!(tab[i] = ft_strjoin(tmp->name, "=")))
				return (NULL);
			tempo = tab[i];
			if (!(tab[i] = ft_strjoin(tab[i], tmp->data)))
				return (NULL);
			free(tempo);
			i++;
		}
		tmp = tmp->next;
	}
	tab[size] = 0;
	return (tab);
}

int				command_bin(char **tab, t_temp *tmp)
{
	pid_t		f;
	char		**tab_env;
	char		**tabpath;
	int			status;

	if (search_env("PATH", tmp, 1, NULL) == 0)
		return (-1);
	if (!(tabpath = build_cmd(tmp, tab[0])))
		exit(1);
	if ((status = cmd_is_here(tabpath)) == -1)
	{
		ft_free_tab(tabpath);
		return (-1);
	}
	if (!(tab_env = c_env(tmp->varenv, lists_size(tmp->varenv))))
		exit(1);
	if ((f = fork()) == 0)
	{
		if (execve(tabpath[status], tab, tab_env) == -1)
			exit(1);
		exit(0);
	}
	if ((f = waitpid(f, &status, WUNTRACED | WCONTINUED)) == -1)
		exit(1);
	ft_free_tab(tab_env);
	ft_free_tab(tabpath);
	return (0);
}
