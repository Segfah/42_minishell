/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 01:51:46 by corozco           #+#    #+#             */
/*   Updated: 2020/08/01 04:52:46 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Printf le pwd fonction a changer!! elle est horrible.
*/

static int		print_pwd(char *str, t_temp *tmp)
{
	tmp->env = getcwd(NULL, 0);
	if (ft_strcmp(str, "pwd") == 0)
	{
		ft_printf("%s\n", tmp->env);
		return (1);
	}
	else if (ft_strncmp(str, "pwd ", 4) == 0)
	{
		ft_printf("pwd: too many arguments\n");
		return (1);
	}
	else
	{
		free(tmp->env);
		return (0);
	}
	free(tmp->env);
	return (0);
}

int		gestion_pwd(char **tabcmd, t_temp *tmp, int i)
{
	if (ft_strncmp(tabcmd[i], "pwd", 3) == 0)
	{
		if (print_pwd(tabcmd[i], tmp))
			return (1);
	}
	return (0);
}
