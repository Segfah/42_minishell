/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 22:43:00 by corozco           #+#    #+#             */
/*   Updated: 2020/10/21 19:25:00 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			gestion_unset(t_temp *tmp)
{
	int			i;
	int			ret;

	i = 0;
	while (tmp->strcmd[i])
		i++;
	if (i == 1)
		ft_printf("unset: not enough arguments\n");
	i = 0;
	while (tmp->strcmd[++i])
	{
		ret = check_env(tmp->strcmd[i], 0);
		if (ret == -1 || ret == 1)
			ft_printf("minishell: unset: `%s': not a valid identifier \n",
					tmp->strcmd[i]);
		else
			deletenode(tmp->varenv, tmp->strcmd[i]);
	}
}
