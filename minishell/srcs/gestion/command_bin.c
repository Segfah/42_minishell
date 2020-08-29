/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:00:48 by lryst             #+#    #+#             */
/*   Updated: 2020/08/29 05:09:36 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
char	**create_env_exec(t_lists *list)
{
	t_lists *tmp;
	char	tab

	tmp = list;
	while (tmp != NULL)
	{
		tmp = tmp->next;
	}
	return (
}
*/

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
	//	ft_printf("[%s]\n", tabpath[*a]);
	}
	free(path);
	return (tabpath);
}

int				command_bin(char **tab, t_temp *tmp)
{
	char		*new_env[] = {NULL};
	pid_t		f;
	pid_t		w;
	int			status;
	char		**tabpath;
	int			i;

	i = -1;
	if (!(tabpath = build_cmd(tmp, tab[0], &i)))
		return (-1);
	f = fork();
	if (f == 0)
	{
		int intento = 0;
		int returno = 0;
		while (tabpath[intento])
		{
			if ((returno = execve(tabpath[intento++], tab, new_env)) == 0)
				exit(0);
		}
		exit(1);
	}
	else
	{
		if ((w = waitpid(f, &status, WUNTRACED | WCONTINUED)) == -1)
			exit(1);
		if (WIFEXITED(status))
			if (WEXITSTATUS(status) == 1)
			{
				ft_free_split(tabpath, i);
				return (-1);
			}
	}
	ft_free_split(tabpath, i);
	return (0);
}
