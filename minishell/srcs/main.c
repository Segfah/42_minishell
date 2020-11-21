/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:00:46 by corozco           #+#    #+#             */
/*   Updated: 2020/10/15 18:01:23 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			initialize_tmp(t_temp *tmp, int ac, char **av)
{
	tmp->env = NULL;
	tmp->prompt = NULL;
	tmp->varenv = NULL;
	tmp->exportenv = NULL;
	tmp->env = NULL;
	tmp->tab[0] = NULL;
	tmp->tab[1] = NULL;
	tmp->hnull = NULL;
	tmp->strcmd = NULL;
	tmp->strcmdin = NULL;
	(void)ac;
	(void)av;
}

/*
** On recalcule le prompt à chaque fois car le path(pwd) va changer quand...
** ...on fait un cd (cd .., cd, cd ~, etc) de cette maniere on aura...
** ...le prompt maj
** ps (trouver une autre maniere de le faire sans fais autant d'appel à getcwd)
*/

void			sighandler(int signum)
{
	char		*prompt;
	char		*env;

	write(1, "\b\b  \n", 5);
	env = getcwd(NULL, 0);
	if ((prompt = ft_prompt(env)) == NULL)
		exit(1);
	ft_printf("\x1b[33m%s\x1b[0m🐰: ", prompt);
	ft_free(env);
	env = NULL;
	ft_free(prompt);
	prompt = NULL;
	(void)signum;
}

void			sighandler2(int signum)
{
	(void)signum;
	write(1, " \b\b \b\b \b", 8);
}

void			launcher(t_temp tmp)
{
	int			ret;

	ret = 1;
	while (ret)
	{
		tmp.env = getcwd(NULL, 0);
		if ((tmp.prompt = ft_prompt(tmp.env)) == NULL)
			general_free(&tmp);
		ft_printf("\x1b[33m%s\x1b[0m🐰: ", tmp.prompt);
		signal(SIGINT, sighandler);
		signal(SIGQUIT, sighandler2);
		ft_free(tmp.env);
		ret = ft_getline(&tmp);
		ft_free(tmp.prompt);
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

int				main(int ac, char **av, char **envp)
{
	t_temp		tmp;

	g_ret = 0;
	initialize_tmp(&tmp, ac, av);
	welcome();
	if (save_env(&tmp.varenv, envp) == -1)
		return (-1);
	if (tmp.varenv == NULL)
		new_list_no_env(&tmp.varenv);
	if (!tmp.hnull)
	{
		if (search_env("HOME", &tmp, 1, NULL) == 1)
		{
			if (search_env("HOME", &tmp, 0, &tmp.hnull) == -1)
				return (1);
		}
		else
		{
			if (!(tmp.hnull = ft_strdup("/")))
				return (1);
		}
	}
	launcher(tmp);
	free_list(tmp.varenv);
	free(tmp.hnull);
	return (0);
}
