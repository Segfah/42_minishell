/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 23:02:07 by corozco           #+#    #+#             */
/*   Updated: 2020/08/19 04:01:49 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		add_list_front(t_lists **head, char *str)
{
	t_lists		*new;
	char		*ss;

	if (!(new = malloc(sizeof(t_lists))))
		exit(1);
	ss = ft_strchr(str, '=');
	if (!(new->data = ft_strdup((ss != NULL) ? ss + 1 : "")))
		exit(1);
	str[ss - str] = 0;
	if (!(new->name = ft_strdup(str)))
		exit(1);
	if (ss)
		str[(int)ft_strlen(str)] = '=';
	new->next = *head;
	*head = new;
}

/*
** fonction qui garde le env dans une liste c
*/

void			save_env(t_lists **head, char **envp)
{
	int			i;

	i = 0;
	*head = NULL;
	while (envp[i])
		i++;
	while (i--)
		add_list_front(head, envp[i]);
}

void			gestion_env(t_temp *tmp)
{
	print_list(tmp->varenv, 1);
}
