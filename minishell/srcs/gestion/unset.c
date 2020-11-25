/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/19 22:43:00 by corozco           #+#    #+#             */
/*   Updated: 2020/11/17 15:40:02 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			gestion_unset(t_temp *tmp)
{
	int			i;
	int			ret;

	i = 0;
	g_ret = 0;
	while (tmp->strcmd[i])
		i++;
	i = 0;
	while (tmp->strcmd[++i])
	{
		ret = check_env(tmp->strcmd[i], 1);
		if (ret == -1 || ret == 1)
		{
			g_ret = 1;
			ft_fprintf(2, "minishell: unset: `%s': not a valid identifier\n",
				tmp->strcmd[i]);
		}
		else
			deletenode(tmp->varenv, tmp->strcmd[i]);
	}
}
