/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist_astring.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 14:00:14 by lryst             #+#    #+#             */
/*   Updated: 2020/11/22 20:53:35 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** fonction qui compte la liste sans les espaces de echo -n
*/

static int		mlist_size(t_cmd *head)
{
	int			i;

	i = 0;
	if (!head)
		return (i);
	while (head)
	{
		i++;
		head = head->next;
	}
	return (i);
}

static int		llist_astring2(t_cmd *head, t_temp *tmp, int *i)
{
	if (head->output)
	{
		if (!(tmp->strcmd[*i] = ft_strdup(head->output)))
			return (-1);
		if (!(tmp->strcmdin[*i] = ft_strdup(head->input)))
			return (-1);
		if (!(tmp->cpytab[(*i)++] = ft_strdup(head->input)))
			return (-1);
	}
	return (0);
}

/*
** Fonction qui modifie strcmd avec la liste, maj + supp des espaces
*/

int				llist_astring(t_cmd *head, t_temp *tmp)
{
	int			i;

	i = 0;
	if (head)
	{
		ft_free_double_tab(tmp->strcmd);
		if (!(tmp->strcmd = malloc(sizeof(char*) * (mlist_size(head) + 1))))
			return (-1);
		if (!(tmp->strcmdin = malloc(sizeof(char*) * (mlist_size(head) + 1))))
			return (-1);
		if (!(tmp->cpytab = malloc(sizeof(char*) * (mlist_size(head) + 1))))
			return (-1);
		while (head)
		{
			if (llist_astring2(head, tmp, &i) == -1)
				return (-1);
			head = head->next;
		}
		tmp->cpytab[i] = 0;
		tmp->strcmd[i] = 0;
		tmp->strcmdin[i] = 0;
	}
	if (!cherche_echo(tmp->strcmd))
		clean_tab2d(tmp->strcmd, tmp->strcmdin);
	return (0);
}
