/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:54:13 by corozco           #+#    #+#             */
/*   Updated: 2020/10/22 16:54:15 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				check_redi(char **cmd, t_temp *tmp, int key)
{
	int			i;

	tmp->fd = 0;
	tmp->fdi = 0;
	i = 0;
	while (cmd[i]) //(cmd == tmp->strcmdin)  // tmp->strcmd
	{
		if (is_redi(cmd[i]))
		{
			if (cmd[i + 1])
			{
				!ft_strcmp(cmd[i + 1], " ") ? i++ : i;
				if (cmd[i + 1] && is_redi(cmd[i + 1]))
				{
					if (key)
						exit(23);
					ft_printf("minishell: syntax error near unexpected token `%s'\n", cmd[i + 1]);
					return (tmp->flag[1] = -1);
				}
			}
			else
			{
				if (key)
						exit(24);
				ft_printf("minishell: syntax error near unexpected token `newline'\n");
				return (tmp->flag[1] = -1);
			}
		}
		(cmd[i] != NULL) ? i++ : i;
	}
	i = 0;
	while (cmd[i]) 
	{
		if (!(ft_strcmp(">", cmd[i])))
		{
			tmp->flag[1] = 1;
			!ft_strcmp(cmd[i + 1], " ") ? i++ : i;
			if (tmp->flag[2] != -1 && simple_redi(tmp->strcmd[i + 1], tmp) == -1)
				return (tmp->flag[1] = -1);
		}
		else if (tmp->flag[2] != -1 && !(ft_strcmp(">>", cmd[i])))
		{
			tmp->flag[1] = 1;
			!ft_strcmp(cmd[i + 1], " ") ? i++ : i;
			if (double_redi(tmp->strcmd[i + 1], tmp) == -1)
				return (tmp->flag[1] = -1);
		}
		else if (!(ft_strcmp("<", cmd[i])))
		{
			tmp->flag[2] = 1;
			!ft_strcmp(cmd[i + 1], " ") ? i++ : i;
			if (contre_redi(tmp->strcmd[i + 1], tmp) == -1)
				return (tmp->flag[2] = -1);
		}
		(cmd[i] != NULL) ? i++ : i;
	}
	return (0);
}

void			skip_redi(char **cmd, t_temp *tmp)
{
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (cmd[i])
	{
		if (!(ft_strcmp(">", cmd[i])) || !(ft_strcmp(">>", cmd[i])) || !(ft_strcmp("<", cmd[i])))
		{
			if (cmd[i] != NULL && cmd[i + 1] != NULL)
			{
				ft_free(cmd[i]);
				ft_free(tmp->strcmd[i]);
				i++;
			}
			if (cmd[i + 1] && !ft_strcmp(cmd[i], " "))  //
			{
				ft_free(cmd[i]);
				ft_free(tmp->strcmd[i]);
				i++;
				ft_free(cmd[i]);
				ft_free(tmp->strcmd[i]);
				i++;
			}
			else
			{
				ft_free(cmd[i]);
				ft_free(tmp->strcmd[i]);
				i++;
			}
		}
		else
		{
			if (cmd[i + 1] != NULL)
			{
				cmd[j] = cmd[i];
				tmp->strcmd[j++] = tmp->strcmd[i++];
			}
		}
	}
	cmd[j] = 0;
	tmp->strcmd[j] = 0;

//	printftab(cmd);
//	printftab(tmp->strcmd);
	clean_tab2d_echo(cmd,tmp->strcmd);
//	printftab(cmd);
//	printftab(tmp->strcmd);
}