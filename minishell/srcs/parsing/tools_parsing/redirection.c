/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:54:13 by corozco           #+#    #+#             */
/*   Updated: 2020/11/19 14:47:49 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				check_redi(char **cmd, t_temp *tmp)
{
	int			i;

	if ((i = check_redi_flag(cmd, tmp)) != 0)
		return (i);
	i = 0;
	while (cmd[i])
	{
		if (check_redi_flag2(cmd, tmp, &i) != 0)
			return (-1);
		(cmd[i] != NULL) ? i++ : i;
	}
	return (0);
}

void			ft_double_free(char *s1, char *s2, int *i)
{
	ft_free(s1);
	ft_free(s2);
	*i += 1;
}

/*
** si hay problemas con las redi poner esto antes
**     ydespues de clean_tab2d_echo(cmd, tmp->strcmd);
**	printftab(cmd);
**	printftab(tmp->strcmd);
*/

static void		copy_mov_pointer(char **cmd, t_temp *tmp, int *i, int *j)
{
	if (cmd[*i] != NULL)
	{
		cmd[*j] = cmd[*i];
		tmp->strcmd[(*j)++] = tmp->strcmd[(*i)++];
	}
}

void			skip_redi(t_temp *tmp, int i, int j)
{
	while (tmp->strcmdin[i])
	{
		if (!(ft_strcmp(">", tmp->strcmdin[i]))
			|| !(ft_strcmp(">>", tmp->strcmdin[i]))
			|| !(ft_strcmp("<", tmp->strcmdin[i])))
		{
			if (tmp->strcmdin[i] != NULL && tmp->strcmdin[i + 1] != NULL)
				ft_double_free(tmp->strcmdin[i], tmp->strcmd[i], &i);
			if (tmp->strcmdin[i + 1] && !ft_strcmp(tmp->strcmdin[i], " "))
			{
				ft_double_free(tmp->strcmdin[i], tmp->strcmd[i], &i);
				ft_double_free(tmp->strcmdin[i], tmp->strcmd[i], &i);
			}
			else
				ft_double_free(tmp->strcmdin[i], tmp->strcmd[i], &i);
		}
		else
			copy_mov_pointer(tmp->strcmdin, tmp, &i, &j);
	}
	tmp->strcmdin[j] = 0;
	tmp->strcmd[j] = 0;
	clean_tab2d_echo(tmp->strcmdin, tmp->strcmd);
	clean_espaces_echo(tmp);
	if (clean_espaces_echo(tmp) == -1)
		general_free(tmp);
}
