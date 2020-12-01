/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 13:58:31 by lryst             #+#    #+#             */
/*   Updated: 2020/12/01 10:08:30 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					isalpha1(char *s)
{
	int i;
	int ret;

	ret = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		if (!(((int)s[i] >= 65 && (int)s[i] <= 90) || ((int)s[i] >= 97 &&
		(int)s[i] <= 122)))
			return (-1);
		ret++;
		i++;
	}
	return (ret);
}

int					check_before_cat_node(char *s1, char *s2)
{
	if (ft_strcmp(s1, " ") && ft_strcmp(s2, " ") && ft_strncmp(s1, "<", 1) &&
	ft_strncmp(s2, "<", 1) && ft_strncmp(s1, ">", 1) && ft_strncmp(s2, ">", 1)
	&& ft_strncmp(s1, "|", 1 && ft_strncmp(s2, "|", 1)))
		return (1);
	return (0);
}

static int			check_echo(char *cmd)
{
	int				i;
	int				check;

	i = 0;
	check = 0;
	if (!cmd)
		return (-1);
	if (ft_strlen(cmd) < 4)
		return (0);
	if (check_echo_2(&check, &i, 'e', cmd) == 1)
	{
		if (check_echo_2(&check, &i, 'c', cmd) == 2)
		{
			if (check_echo_2(&check, &i, 'h', cmd) == 3)
			{
				if (check_echo_2(&check, &i, 'o', cmd) == 4)
					return (1);
			}
		}
	}
	return (0);
}

int					cherche_echo(char **tab)
{
	int			i;

	i = 0;
	while (tab[i])
	{
		if (check_echo(tab[i]))
			return (1);
		i++;
	}
	return (0);
}

void				separator_string(t_cmd **cmd, char *str, t_temp *tmp)
{
	int		i;
	t_cmd	*new;

	i = 0;
	if (!tmp)
		return ;
	if (!(tmp->strcmd = ft_split_strcmd(str, 1)))
		general_free(tmp);
	while (tmp->strcmd[i])
	{
		if (!(new = ft_lstnew_cmd(tmp->strcmd[i], tmp)))
			general_free(tmp);
		ft_lstadd_back_cmd(cmd, new);
		i++;
	}
	remove_null_node(cmd);
	while (strcat_cmd(cmd) == 1)
		;
	remove_null_node(cmd);
	remove_space_node(cmd);
}
