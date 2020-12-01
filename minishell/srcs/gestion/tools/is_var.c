/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_var.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 10:03:03 by lryst             #+#    #+#             */
/*   Updated: 2020/12/01 10:03:19 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_var(t_lists *revar, char *tabcmd, int *i, int save)
{
	int		size;
	char	*tmp;

	if (!(tmp = (char*)malloc(sizeof(char) * (*i - save) + 1)))
		return (-1);
	size = 0;
	while (save < *i)
		tmp[size++] = tabcmd[save++];
	tmp[size] = '\0';
	while (revar)
	{
		if (!revar->name && !revar->data)
			break ;
		if (ft_strcmp(revar->name, tmp) == 0)
		{
			ft_free(tmp);
			return (1);
		}
		revar = revar->next;
	}
	(*i)--;
	ft_free(tmp);
	return (0);
}
