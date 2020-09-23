/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 22:10:58 by lryst             #+#    #+#             */
/*   Updated: 2020/09/23 18:51:01 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <errno.h>

void			gestion_cd(char *str, t_temp *tmp)
{
	char		*path;
	int			i;

	i = 2;
	if (ft_strncmp(str, "cd ", 3) == 0)
	{
		if (!(path = (char*)malloc(sizeof(char) * ft_strlen(str) - 2)))
		{
			ft_printf("gestion_cd2, error malloc\n");
			exit(0);
		}
		tmp->env = getcwd(NULL, 0);
		while (str[i++] != '\0')
			path[i - 3] = str[i];
		if (chdir(path) != 0)
		{
			g_ret = 1;
			ft_printf("cd: %s: %s\n", strerror(errno), path);
		}
		else
		{
			g_ret = 0;
			change_list(tmp->varenv, "OLDPWD", tmp->env);
			free(tmp->env);
			tmp->env = getcwd(NULL, 0);
			change_list(tmp->varenv, "PWD", tmp->env);
		}
		free(tmp->env);
		free(path);
	}
}
