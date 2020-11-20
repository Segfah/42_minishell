/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_env_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/22 15:36:42 by corozco           #+#    #+#             */
/*   Updated: 2020/08/22 15:42:40 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_nb_exit(int exi)
{
	exit(exi);
}

int				check_env(char *str, int key)
{
	int			i;

	if (key == 1)
	{
		if ((ft_isalpha(str[0]) == 0) && str[0] != '_')
			return (-1);
		i = 1;
	}
	else
		i = 0;
	while (str[i] && str[i] != '=')
	{
		if (ft_isalnum(str[i]) || str[i] == '_')
			i++;
		else
			return (-1);
	}
	if (str[i] == '=')
		return (1);
	return (0);
}
