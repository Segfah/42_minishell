/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:00:46 by corozco           #+#    #+#             */
/*   Updated: 2020/08/04 02:34:02 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			add_list_front(t_lists **head, char *str)
{
	t_lists		*new;

	if (!(new = malloc(sizeof(t_lists))))
		exit(1);
	if (!(new->content = ft_strdup(str)))
		exit(1);
	new->next = *head;
	*head = new;
}

void			free_list(t_lists *test)
{
	t_lists		*tmp;

	while (test != NULL)
	{
		tmp = test->next;
		free(test->content);
		free(test);
		test = tmp;
	}
}

void			save_env(t_lists **head, char **envp)
{
	int			i;

	i = 0;
	*head =NULL;
	while (envp[i])
		i++;
	while (i--)
		add_list_front(head, envp[i]);
}

/*
** On recalcule le prompt à chaque fois car le path(pwd) va changer quand...
** ...on fait un cd (cd .., cd, cd ~, etc) de cette maniere on aura...
** ...le prompt maj
** ps (trouver une autre maniere de le faire sans fais autant d'appel à getcwd)
*/

int				launcher(t_temp tmp)
{
	char		*prompt;

	while (1)
	{
		tmp.env = getcwd(NULL, 0);
		prompt = ft_prompt(tmp.env);
		ft_printf("\x1b[33m%s\x1b[0m🐰: ", prompt);
		free(tmp.env);
		ft_getline(&tmp);
		free(prompt);
	}
}

/*
** tmp.env = variable qui prend le getcwd (get working directory pathname)(pwd);
** launcher = fonction principal (boucle infini)
*/

int				main(int ac, char **av, char **envp)
{
	t_temp		tmp;

	welcome();
	save_env(&tmp.varenv, envp);
	launcher(tmp);
	free_list(tmp.varenv);
	(void)ac;
	(void)av;
	return (0);
}
