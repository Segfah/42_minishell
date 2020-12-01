/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 12:11:19 by lryst             #+#    #+#             */
/*   Updated: 2020/11/26 01:10:49 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			printftab(char **tab)
{
	int			i;

	i = -1;
	if (tab)
	{
		ft_printf("----printtab----\n");
		while (tab[++i])
			ft_printf("---[%d], --- [%s]\n", i, tab[i]);
		ft_printf("-----------------\n");
	}
}

void			printflist(t_cmd *cmd)
{
	t_cmd		*tmp;

	tmp = cmd;
	ft_printf("----printlist----\n");
	while (tmp)
	{
		ft_printf("list in[%s] out[%s]\n", tmp->input, tmp->output);
		tmp = tmp->next;
	}
	ft_printf("-----------------\n");
}
