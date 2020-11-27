/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_slash.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:37:22 by lryst             #+#    #+#             */
/*   Updated: 2020/11/24 11:48:37 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_count_word_slash_2(char *s, int *i, int *n)
{
	while (s[*i] && s[*i] != ' ' && s[*i] != '"' && s[*i] != '\'' &&
	s[*i] != '$' && s[*i] != '\\')
		(*i)++;
	(*n)++;
}

void	ft_count_word_slash(char *s, int *i, int *n)
{
	int count;

	count = 0;
	while (s[*i] && s[*i] == '\\')
	{
		(*i)++;
		count++;
	}
	if ((count % 2) == 0)
		(*n)++;
	else if ((count % 2) == 1 && count > 1)
	{
		i--;
		(*n)++;
	}
	else if ((count % 2) == 1 && count == 1 && (s[*i + 1] == '\'' ||
	s[*i + 1] == '"' || s[*i] == '"' || s[*i] == '\''))
	{
		(*i)++;
		(*n)++;
	}
	else
		ft_count_word_slash_2(s, i, n);
}

char	*ft_fill_slash_2(char *s, int *i, char *tab, int save)
{
	while (s[*i] && s[*i] != ' ' && s[*i]
		!= '"' && s[*i] != '\'' && s[*i] != '\\')
		(*i)++;
	return (tab = copy(s, i, save));
}

char	*ft_fill_slash(char *s, int *i, char *tab)
{
	int count;
	int save;

	count = 0;
	save = *i;
	while (s[*i] && s[*i] == '\\')
	{
		(*i)++;
		count++;
	}
	if ((count % 2) == 0)
		return (tab = copy(s, i, save));
	else if ((count % 2) == 1 && count > 1)
	{
		(*i)--;
		return (tab = copy(s, i, save));
	}
	else if ((count % 2) == 1 && count == 1 && (s[*i] == '\'' ||
		s[*i] == '"'))
	{
		(*i)++;
		return (tab = copy(s, i, save));
	}
	return (ft_fill_slash_2(s, i, tab, save));
}
