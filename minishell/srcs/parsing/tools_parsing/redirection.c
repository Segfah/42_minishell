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

void			ft_exit(int exi)
{
	exit(exi);
}

int				check_redi_simple_error(char **cmd, t_temp *tmp, int i)
{
	if (search_error_redi1(cmd[i]) == -3)
	{
		ft_printf("minishell: syntax error near unexpected token `>'\n");
		return (tmp->flag[1] = -1);
	}
	if (search_error_redi1(cmd[i]) < -3)
	{
		ft_printf("minishell: syntax error near unexpected token `>>'\n");
		return (tmp->flag[1] = -1);
	}
	if (search_error_redi2(cmd[i]) == -1)
	{
		ft_printf("minishell: syntax error near unexpected token `<'\n");
		return (tmp->flag[1] = -1);
	}
	return (0);
}

int				check_redi_flag(char **cmd, t_temp *tmp, int key)
{
	int			i;

	tmp->fd = 0;
	tmp->fdi = 0;
	i = 0;
	while (cmd[i])
	{
		if (check_redi_simple_error(cmd, tmp, i) != 0)
			return (-1);
		if (is_redi(cmd[i]))
		{
			if (cmd[i + 1])
			{
				!ft_strcmp(cmd[i + 1], " ") ? i++ : i;
				if (cmd[i + 1] && is_redi(cmd[i + 1]))
				{
					key ? ft_exit(23) : 0;
					ft_printf("minishell: syntax error near unexpected token `%s'\n", cmd[i + 1]);
					return (tmp->flag[1] = -1);
				}
			}
			else
			{
				key ? ft_exit(24) : 0;
				ft_printf("minishell: syntax error near unexpected token `newline'\n");
				return (tmp->flag[1] = -1);
			}
		}
		(cmd[i] != NULL) ? i++ : i;
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
		if (!(ft_strcmp(">", cmd[i])))
		{
			tmp->flag[1] = 1;
			!ft_strcmp(cmd[i + 1], " ") ? i++ : i;
			if (tmp->flag[2] != -1 && simple_redi(tmp->strcmd[i + 1], tmp, key) == -1)
				return (tmp->flag[1] = -1);
		}
		else if (tmp->flag[2] != -1 && !(ft_strcmp(">>", cmd[i])))
		{
			tmp->flag[1] = 1;
			!ft_strcmp(cmd[i + 1], " ") ? i++ : i;
			if (double_redi(tmp->strcmd[i + 1], tmp, key) == -1)
				return (tmp->flag[1] = -1);
		}
		else if (!(ft_strcmp("<", cmd[i])))
		{
			tmp->flag[2] = 1;
			!ft_strcmp(cmd[i + 1], " ") ? i++ : i;
			if (contre_redi(tmp->strcmd[i + 1], tmp, key) == -1)
				return (tmp->flag[2] = -1);
		}
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

void			skip_redi(char **cmd, t_temp *tmp)
{
	int			i;
	int			j;

	i = 0;
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
		{
			if (cmd[i] != NULL)
			{
				cmd[j] = cmd[i];
				tmp->strcmd[j++] = tmp->strcmd[i++];
			}
		}
	}
	cmd[j] = 0;
	tmp->strcmd[j] = 0;
/*
	printftab(cmd);
	printftab(tmp->strcmd);
*/
	clean_tab2d_echo(cmd, tmp->strcmd);
/*
	printftab(cmd);
	printftab(tmp->strcmd);
*/
}
