/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:00:48 by lryst             #+#    #+#             */
/*   Updated: 2020/10/15 18:02:38 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

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

void			sighandlerrr(int signum)
{
	write(1, "\b\b  \n", 5);
	(void)signum;
}

void			sighandlerrr2(int signum)
{
	write(1, "Quit: 3  \n", 10);
	(void)signum;
}

int				command_bin(char **tab, t_temp *tmp)
{
	pid_t		f;
	char		**tab_env;

	if (!(tab_env = c_env(tmp->varenv, lists_size(tmp->varenv))))
		exit(1);
	if ((f = fork()) == 0)
	{
		if (tmp->flag[1] == 1)
			dup2(tmp->fd, 1);
		if (tmp->flag[1] == 2)
			dup2(tmp->fd, 0);
		if (!tmp->tabpath)
		{
			if (execve(tab[0], tab, tab_env) == -1)
			{
				ft_printf("minishell: %s: %s\n", tab[0], strerror(errno));
				g_ret = 1;
				exit(1);
			}
			exit(0);
		}
		else if (execve(tmp->tabpath[tmp->status], tab, tab_env) == -1)
		{
			g_ret = 1;
			exit(1);
		}
		exit(0);
	}
	else
	{
		signal(SIGQUIT, sighandlerrr2);
		signal(SIGINT, sighandlerrr);
	}
	if ((f = waitpid(f, &tmp->status, WUNTRACED | WCONTINUED)) == -1)
		exit(1);
	ft_free_tab(tab_env);
	tmp->tabpath ? ft_free_tab(tmp->tabpath) : 0;
	return (0);
}
