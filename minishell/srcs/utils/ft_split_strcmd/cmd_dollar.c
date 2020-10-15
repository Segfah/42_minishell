/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:26:11 by lryst             #+#    #+#             */
/*   Updated: 2020/10/15 20:21:07 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_count_word_dollar(char *s, int *i, int *n)
{
	int count;

	count = *n;
	(*i)++;
	if (s[*i] == '?')
	{
		(*i)++;
		(*n)++;
	}
	else if (s[*i] == '"' || s[*i] == '\'')
		*n = adeline(s, s[*i], count, i);
	else if (s[*i] == ' ' || s[*i] == '\0' || s[*i] == '\\')
		(*n)++;
	else
	{
		while (s[*i] && ((s[*i] > 47 && s[*i] < 58) || (s[*i] > 64 &&
		s[*i] < 91) || (s[*i] > 96 && s[*i] < 123)))
			(*i)++;
		(*n)++;
	}
}

char		*ft_fill_dollar(char *s, int *i, char *tab)
{
	int save;

	save = *i;
	(*i)++;
	if (s[*i] == '?')
	{
		(*i)++;
		return (tab = copy(s, i, save));
	}
	else if (s[*i] == '"' || s[*i] == '\'')
	{
		adeline(s, s[*i], 0, i);
		if (save < *i)
			return (tab = copy(s, i, save));
	}
	else if (s[*i] == ' ' || s[*i] == '\0' || s[*i] == '\\')
		return (tab = ft_strdup("$\0"));
	else
	{
		while (s[*i] && ((s[*i] > 47 && s[*i] < 58) || (s[*i] > 64 &&
			s[*i] < 91) || (s[*i] > 96 && s[*i] < 123)))
			(*i)++;
		return (tab = copy(s, i, save));
	}
	return (NULL);
}
