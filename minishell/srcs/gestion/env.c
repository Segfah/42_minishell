/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 23:02:07 by corozco           #+#    #+#             */
/*   Updated: 2020/11/16 22:55:02 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		add_list_front(t_lists **head, char *str)
{
	t_lists		*new;
	char		*ss;

	if (!(new = malloc(sizeof(t_lists))))
		return (-1);
	ss = ft_strchr(str, '=');
	if (!(new->data = ft_strdup((ss != NULL) ? ss + 1 : "")))
		return (-1);
	str[ss - str] = 0;
	if (!(new->name = ft_strdup(str)))
		return (-1);
	if (ss)
		str[(int)ft_strlen(str)] = '=';
	new->next = *head;
	*head = new;
	return (0);
}

/*
** fonction qui garde le env dans une liste c
*/

int				save_env(t_lists **head, char **envp)
{
	int			i;

	i = 0;
	*head = NULL;
	while (envp[i])
		i++;
	while (i--)
	{
		if (add_list_front(head, envp[i]) == -1)
		{
			free_list(*head);
			return (-1);
		}
	}
	return (0);
}

void			gestion_env(char **strcmd, t_temp *tmp)
{
	g_ret = 0;
	if (!strcmd[1])
	{
		if (tmp->flag[1] == 1)
		{
			tmp->oldfd = dup(1);
			dup2(tmp->fd, 1);
		}
		print_list(tmp->varenv, 1);
		(tmp->flag[1] == 1) ? dup2(tmp->oldfd, 1) : 0;
		return ;
	}
	else
	{
		g_ret = 127;
		ft_fprintf(2, "env: %s: No such file or directory\n", strcmd[1]);
	}
}
