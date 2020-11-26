/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/03 15:00:48 by lryst             #+#    #+#             */
/*   Updated: 2020/11/19 16:11:22 by lryst            ###   ########.fr       */
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
			ft_free(tempo);
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

	g_ret = 1;
	if (!(tab_env = c_env(tmp->varenv, lists_size(tmp->varenv))))
		exit(1);
	if ((f = fork()) == 0)
		command_bin_2(tab_env, tab, tmp);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, sighandlerrr2);
//		signal(SIGINT, sighandlerrr);
	}
	if ((f = waitpid(f, &tmp->status, WUNTRACED | WCONTINUED)) == -1)
		exit(1);
	if (WIFSIGNALED(tmp->status))
		ft_printf("\n");
	signal(SIGINT, sighandlerrr);
	ft_free_tab(tab_env);
	if (WIFEXITED(tmp->status))
		command_bin_3(tmp);
	return (0);
}
