/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:00:46 by corozco           #+#    #+#             */
/*   Updated: 2020/12/01 12:25:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "msignal.h"

void			launcher(t_temp tmp, int ac, char **av)
{
	int			ret;

	ret = 1;
	if (ac > 1)
		ret = ft_getline(&tmp, av, 0);
	else
	{
		while (ret)
		{
			tmp.env = getcwd(NULL, 0);
			if ((tmp.prompt = ft_prompt(tmp.env)) == NULL)
				general_free(&tmp);
			ft_printf("\x1b[33m%s\x1b[0m🐰: ", tmp.prompt);
			signal(SIGINT, sighandler);
			signal(SIGQUIT, sighandler2);
			ft_free(tmp.env);
			ret = ft_getline(&tmp, NULL, 0);
			ft_free(tmp.prompt);
		}
	}
}

/*
** tmp.env = variable qui prend le getcwd (get working directory pathname)(pwd);
** launcher = fonction principal (boucle infini)
*/

static int		new_list_no_env(t_lists **head)
{
	t_lists		*new;

	if (!(new = malloc(sizeof(t_lists))))
		return (-1);
	new->data = NULL;
	new->name = NULL;
	new->next = *head;
	*head = new;
	return (0);
}

int				creating_env(t_temp *tmp)
{
	tmp->env = getcwd(NULL, 0);
	if (new_list_no_env(&tmp->varenv) == -1)
		return (-1);
	if (search_env("PWD", tmp, 1, NULL) == 0)
	{
		if ((lback(&tmp->varenv, "PWD", tmp->env)) == -1)
			return (-1);
		if ((lback(&tmp->varenv, "OLDPWD", NULL)) == -1)
			return (-1);
		if ((lback(&tmp->varenv, "SHLVL", "1")) == -1)
			return (-1);
	}
	ft_free(tmp->env);
	return (0);
}

int				launch_main(t_temp *tmp, int ac, char **av, char **envp)
{
	g_ret = 0;
	initialize_tmp(tmp, ac, av);
	if (save_env(&tmp->varenv, envp) == -1)
		return (-1);
	if (tmp->varenv == NULL)
		if (creating_env(tmp) == -1)
			return (-1);
	if (!tmp->hnull)
	{
		if (search_env("HOME", tmp, 1, NULL) == 1)
		{
			if (search_env("HOME", tmp, 0, &tmp->hnull) == -1)
				return (-1);
		}
		else
		{
			if (!(tmp->hnull = ft_strdup("/")))
				return (-1);
		}
	}
	return (0);
}

int				main(int ac, char **av, char **envp)
{
	t_temp		tmp;

	if (ac < 2)
	{
		welcome();
		if (launch_main(&tmp, ac, av, envp) == -1)
			return (-1);
		launcher(tmp, ac, NULL);
		free_list(tmp.varenv);
		free(tmp.hnull);
		write(1, "exit\n", 5);
	}
	else if (ac == 3)
	{
		if (!ft_strcmp("-c", av[1]))
		{
			launch_main(&tmp, ac, av, envp);
			launcher(tmp, ac, av);
			free_list(tmp.varenv);
			free(tmp.hnull);
			return (g_ret);
		}
	}
	return (0);
}
