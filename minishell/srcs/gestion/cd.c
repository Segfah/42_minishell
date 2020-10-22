/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 22:10:58 by lryst             #+#    #+#             */
/*   Updated: 2020/10/21 19:27:07 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <errno.h>

char			*cp_str(char *str, t_temp *tmp)
{
	char		*tmp_str;
	char		*new_str;
	int			size;
	int			i;
	int			j;

	tmp_str = NULL;
	new_str = NULL;
	if (search_env("HOME", tmp, 1, NULL))
	{
		search_env("HOME", tmp, 0, &tmp_str);
		size = ft_strlen(str) + ft_strlen(tmp_str);
		if (!(new_str = malloc(sizeof(char) * size + 1)))
			return (NULL);
	}
	else
	{
		if (!(tmp_str = ft_strdup(tmp->hnull)))
			return (NULL);
		size = ft_strlen(str) + ft_strlen(tmp->hnull);
		if (!(new_str = malloc(sizeof(char) * size + 1)))
			return (NULL);
	}
	i = -1;
	while (tmp_str[++i])
		new_str[i] = tmp_str[i];
	j = 1;
	while (str[j])
		new_str[i++] = str[j++];
	new_str[i] = 0;
	ft_free(tmp_str);
	ft_free(str);
	return (new_str);
}

void			gestion_cd(char **strcmd, t_temp *tmp)
{
	char *home;

	home = NULL;
	tmp->env = getcwd(NULL, 0);
	g_ret = 0;
	if (strcmd[1] != NULL)
	{
		printf("------>[%s]\n", strcmd[1]);
		if (!ft_strncmp(strcmd[1], "~", 1))
			strcmd[1] = cp_str(strcmd[1], tmp);
		if (chdir(strcmd[1]) != 0 && (g_ret = 1))
			ft_printf("cd: %s: %s\n", strerror(errno), strcmd[1]);
	}
	else
	{
		search_env("HOME", tmp, 0, &home);
		if (home)
		{
			if (chdir(home) != 0 && (g_ret = 1))
				ft_printf("cd: %s: %s\n", strerror(errno), home);
		}
		else
			(g_ret = 1) ? write(1, "minishell: cd: HOME not set\n", 28) : 0;
		home ? ft_free(home) : 0;
	}
	!g_ret ? change_list(tmp->varenv, "OLDPWD", tmp->env) : 0;
	ft_free(tmp->env);
	tmp->env = getcwd(NULL, 0);
	change_list(tmp->varenv, "PWD", tmp->env);
	ft_free(tmp->env);
}
