/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_option.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:21:16 by lryst             #+#    #+#             */
/*   Updated: 2020/12/01 12:26:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			print_0(char n)
{
	write(1, &n, 1);
	g_ret = 0;
	return (0);
}

int			ft_check_option_echo(char *s)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(s);
	if (s[i] == '-')
	{
		if (s[i + 1])
			i++;
		while (s[i] && s[i] == 'n')
			i++;
	}
	if (i == len)
		return (i);
	return (0);
}

int			echo_cote_space(t_temp *tmp)
{
	int		count;
	char	*str;

	count = 0;
	if (tmp->strcmdin[1] == NULL)
		return (print_0('\n'));
	if (tmp->strcmdin[1] && tmp->strcmdin[2] &&
	((ft_check_option_echo(tmp->strcmd[2]) != 0) ||
	ft_strcmp(tmp->strcmdin[1], " ") == 0))
		return (1);
	str = ft_newstring(0);
	while (tmp->strcmdin[count] &&
	(ft_strcmp(tmp->strcmdin[count], " ") != 0))
	{
		str = ft_strjoinfree(str, tmp->strcmd[count]);
		count++;
	}
	ft_fprintf(2, "minishell: %s: command not found\n", str);
	ft_free(str);
	return (0);
}

int			check_multi_options(t_temp *tmp, int *i, int *n)
{
	while (tmp->strcmdin[*i])
	{
		if (ft_check_option_echo(tmp->strcmd[*i]) != 0)
		{
			if (tmp->strcmdin[(*i) + 1] == NULL)
			{
				(tmp->flag[1] == 1) ? dup2(tmp->oldfd, 1) : 0;
				return (0);
			}
			if (tmp->strcmdin[(*i) + 1] &&
			ft_strcmp(tmp->strcmdin[(*i) + 1], " ") == 0)
			{
				*n = 2;
				(*i)++;
			}
			else
				break ;
		}
		else
			break ;
		(*i)++;
	}
	return (1);
}
