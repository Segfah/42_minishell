/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redi_flag.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:54:13 by corozco           #+#    #+#             */
/*   Updated: 2020/11/19 14:47:49 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		mall_nd_espaces(char **cmd)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (cmd[i + 1] && !ft_strcmp(cmd[i], " ")
			&& !ft_strcmp(cmd[i + 1], " "))
			j++;
		i++;
	}
	if (i > 0 && !ft_strcmp(cmd[i - 1], " "))
		j++;
	return (i - j);
}

static int		change_tab(t_temp *tmp, char **s1, char **s2)
{
	int			i;
	int			j;

	i = -1;
	j = 0;
	while (tmp->strcmdin[++i])
	{
		if (ft_strcmp(tmp->strcmdin[i], " "))
		{
			if (!(s1[j] = ft_strdup(tmp->strcmdin[i]))
				|| !(s2[j++] = ft_strdup(tmp->strcmd[i])))
				return (-1);
		}
		else if (tmp->strcmdin[i + 1] && !ft_strcmp(tmp->strcmdin[i], " ")
			&& ft_strcmp(tmp->strcmdin[i + 1], " "))
		{
			if (!(s1[j] = ft_strdup(tmp->strcmdin[i]))
				|| !(s2[j++] = ft_strdup(tmp->strcmd[i])))
				return (-1);
		}
	}
	s1[j] = NULL;
	s2[j] = NULL;
	return (0);
}

int				clean_espaces_echo(t_temp *tmp)
{
	int			len;
	char		**s1;
	char		**s2;

	len = mall_nd_espaces(tmp->strcmdin);
	if (!(s1 = malloc(sizeof(char**) * len + 1)))
		return (-1);
	if (!(s2 = malloc(sizeof(char**) * len + 1)))
		return (-1);
	if (change_tab(tmp, s1, s2) == -1)
		return (-1);
	ft_free_double_tab(tmp->strcmdin);
	ft_free_double_tab(tmp->strcmd);
	tmp->strcmdin = s1;
	tmp->strcmd = s2;
	return (0);
}
