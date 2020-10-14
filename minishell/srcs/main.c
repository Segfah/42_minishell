/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:00:46 by corozco           #+#    #+#             */
/*   Updated: 2020/10/14 14:37:03 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			initialize_tmp(t_temp *tmp)
{
	tmp->env = NULL;
	tmp->prompt = NULL;
	tmp->varenv = NULL;
	tmp->exportenv = NULL;
	tmp->env = NULL;
	tmp->tab[0] = NULL;
	tmp->tab[1] = NULL;
	tmp->hnull = NULL;
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
	free(env);
	free(prompt);
	(void)signum;
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
		free(tmp.env);
		tmp.env = NULL;
		ret = ft_getline(&tmp);
		free(tmp.prompt);
		tmp.prompt = NULL;
	}
}

/*
** tmp.env = variable qui prend le getcwd (get working directory pathname)(pwd);
** launcher = fonction principal (boucle infini)
*/

int				main(int ac, char **av, char **envp)
{
	t_temp		tmp;

	g_ret = 0;
	initialize_tmp(&tmp);
	welcome();
	if (save_env(&tmp.varenv, envp) == -1)
		return (-1);
	launcher(tmp);
	free_list(tmp.varenv);
	(void)ac;
	(void)av;
	return (0);
}
