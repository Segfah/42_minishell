/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 22:10:58 by lryst             #+#    #+#             */
/*   Updated: 2020/11/25 18:49:08 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <string.h>
#include <errno.h>

char			*cp_str_2(int size, char *tmp_str, char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = -1;
	new_str = NULL;
	if (!(new_str = malloc(sizeof(char) * size + 1)))
		return (NULL);
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

char			*cp_str(char *str, t_temp *tmp)
{
	char		*tmp_str;
	int			size;

	tmp_str = NULL;
	if (search_env("HOME", tmp, 1, NULL))
	{
		if (search_env("HOME", tmp, 0, &tmp_str) == -1)
			general_free(tmp);
		size = ft_strlen(str) + ft_strlen(tmp_str);
	}
	else
	{
		if (!(tmp_str = ft_strdup(tmp->hnull)))
			return (NULL);
		size = ft_strlen(str) + ft_strlen(tmp->hnull);
	}
	return (cp_str_2(size, tmp_str, str));
}

void			gestion_cd_2(char *home, t_temp *tmp)
{
	if (search_env("HOME", tmp, 1, NULL) == 1)
		if (search_env("HOME", tmp, 0, &home) == -1)
			general_free(tmp);
	if (home)
	{
		if (!ft_strcmp(home, ""))
			;
		else if (chdir(home) != 0 && (g_ret = 1))
			ft_fprintf(2, "minishell: cd: %s: %s\n", home, strerror(errno));
	}
	else
		(g_ret = 1) ? write(2, "minishell: cd: HOME not set\n", 28) : 0;
	home ? ft_free(home) : 0;
}

void			gestion_cd(char **strcmd, t_temp *tmp)
{
	char *home;

	home = NULL;
	tmp->env = getcwd(NULL, 0);
	if (!(g_ret = 0) && strcmd[1] != NULL)
	{
		if (!ft_strncmp(strcmd[1], "~", 1))
			if (!(strcmd[1] = cp_str(strcmd[1], tmp)))
				general_free(tmp);
		if (!ft_strcmp(strcmd[1], ""))
			;
		else if (chdir(strcmd[1]) != 0 && (g_ret = 1))
			ft_fprintf(2, "minishell: cd: %s: %s\n"
				, strcmd[1], strerror(errno));
	}
	else
		gestion_cd_2(home, tmp);
	if (search_env("OLDPWD", tmp, 1, NULL) == 1)
		!g_ret ? change_list(tmp->varenv, "OLDPWD", tmp->env, tmp) : 0;
	ft_free(tmp->env);
	tmp->env = getcwd(NULL, 0);
	if (search_env("PWD", tmp, 1, NULL) == 1)
		change_list(tmp->varenv, "PWD", tmp->env, tmp);
	ft_free(tmp->env);
}
