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

int				check_redi_flag2(char **cmd, t_temp *tmp, int key, int *i)
{
	if (!(ft_strcmp(">", cmd[*i])))
	{
		tmp->flag[1] = 1;
		!ft_strcmp(cmd[*i + 1], " ") ? (*i)++ : *i;
		if (tmp->flag[2] != -1
			&& simple_redi(tmp->strcmd[*i + 1], tmp, key) == -1)
			return (tmp->flag[1] = -1);
	}
	else if (tmp->flag[2] != -1 && !(ft_strcmp(">>", cmd[*i])))
	{
		tmp->flag[1] = 1;
		!ft_strcmp(cmd[*i + 1], " ") ? (*i)++ : *i;
		if (double_redi(tmp->strcmd[*i + 1], tmp, key) == -1)
			return (tmp->flag[1] = -1);
	}
	else if (!(ft_strcmp("<", cmd[*i])))
	{
		tmp->flag[2] = 1;
		!ft_strcmp(cmd[*i + 1], " ") ? (*i)++ : *i;
		if (contre_redi(tmp->strcmd[*i + 1], tmp, key) == -1)
			return (tmp->flag[2] = -1);
	}
	return (0);
}

int				check_redi(char **cmd, t_temp *tmp, int key)
{
	int			i;

	if ((i = check_redi_flag(cmd, tmp, key)) != 0)
		return (i);
	i = 0;
	while (cmd[i])
	{
		if (check_redi_flag2(cmd, tmp, key, &i) != 0)
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

void			copy_mov_pointer(char **cmd, t_temp *tmp, int *i, int *j)
{
	if (cmd[*i] != NULL)
	{
		cmd[*j] = cmd[*i];
		tmp->strcmd[(*j)++] = tmp->strcmd[(*i)++];
	}
}

void			skip_redi(char **cmd, t_temp *tmp, int i)
{
	int			j;

	j = 0;
	while (cmd[i])
	{
		if (!(ft_strcmp(">", cmd[i])) || !(ft_strcmp(">>", cmd[i]))
			|| !(ft_strcmp("<", cmd[i])))
		{
			if (cmd[i] != NULL && cmd[i + 1] != NULL)
				ft_double_free(cmd[i], tmp->strcmd[i], &i);
			if (cmd[i + 1] && !ft_strcmp(cmd[i], " "))
			{
				ft_double_free(cmd[i], tmp->strcmd[i], &i);
				ft_double_free(cmd[i], tmp->strcmd[i], &i);
			}
			else
				ft_double_free(cmd[i], tmp->strcmd[i], &i);
		}
		else
			copy_mov_pointer(cmd, tmp, &i, &j);
	}
	cmd[j] = 0;
	tmp->strcmd[j] = 0;
	clean_tab2d_echo(cmd, tmp->strcmd);
}
