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

void			gestion_unset(t_temp *tmp, int key)
{
	int			i;
	int			ret;

	i = 0;
	while (tmp->strcmd[i])
		i++;
	i = 0;
	while (tmp->strcmd[++i])
	{
		ret = check_env(tmp->strcmd[i], 1);
		if (ret == -1 || ret == 1)
		{
			if (key)
				exit(22);
			ft_printf("minishell: unset: `%s': not a valid identifier \n",
				tmp->strcmd[i]);
		}
		else
			deletenode(tmp->varenv, tmp->strcmd[i]);
	}
}
