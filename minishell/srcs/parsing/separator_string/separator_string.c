/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 13:58:31 by lryst             #+#    #+#             */
/*   Updated: 2020/11/02 14:36:52 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			isalpha1(char *s)
{
	int i;
	int ret;

	ret = 0;
	i = 0;
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

int			strcat_cmd(t_cmd **cmd)
{
	t_cmd *tmp;
	int i;

	tmp = *cmd;
	i = 0;
	while (tmp)
	{
		if (tmp->next && (isalpha1(tmp->output) > 0) &&
		(isalpha1(tmp->next->output) > 0))
		{
			//printf("\n\n---------------\n");
			//printf("tmp->input = [%s]\n", tmp->input);
			//printf("tmp->next->input = [%s]\n", tmp->next->input);
			//printf("tmp->output = [%s]\n", tmp->output);
			//printf("tmp->next->output = [%s]\n", tmp->next->output);
			//printf("---------------\n\n");
			//printf("input before -> [%s] | ", tmp->input);
			if ((tmp->input = ft_strcatdup(tmp->input, tmp->next->input)))
				tmp->next->input = NULL;
			//while (1);
			//printf("input after -> [%s]\n", tmp->input);
			//printf("output before -> [%s] | ", tmp->output);
			if ((tmp->output = ft_strcatdup(tmp->output, tmp->next->output)))
				tmp->next->output = NULL;
			i = 1;
			//while (1);
			break ;
		}
		tmp = tmp->next;
		
	}
	remove_null_node(cmd);
	return (i);
}

static int			check_echo_2(int *check, int *i, char c, char *s)
{
	if (s && s[*i] && (s[*i] == c || s[*i] == c - 40))
	{
		*check += 1;
		(*i)++;
		return (*check);
	}
	*check = 0;
	return (0);
}

static int			check_echo(char *cmd) // poner una key para activarlo si necesitamos en la cadena
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

int				cherche_echo(char **tab)
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



void			separator_string(t_cmd **cmd, char *str, t_temp *tmp)
{
	int		i;
	t_cmd	*new;

	i = 0;
	if (!tmp)
	return ;
	tmp->strcmd = ft_split_strcmd(str, 1);
	while (tmp->strcmd[i])
	{
		new = ft_lstnew_cmd(tmp->strcmd[i], tmp);
		ft_lstadd_back_cmd(cmd, new);
		i++;
	}
	while (strcat_cmd(cmd) == 1)
		strcat_cmd(cmd);
	remove_null_node(cmd);
	remove_space_node(cmd);
}
