/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adelines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 22:21:10 by lryst             #+#    #+#             */
/*   Updated: 2020/10/15 21:31:20 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			adeline2(char *s, char c, int n, int *i)
{
	while (s[*i] && s[*i] == c)
		(*i)++;
	return (n + 1);
}

int			adeline(char *s, char cote, int n, int *i)
{
	int j;

	j = *i + 1;
	while (s[j] && s[j] != cote)
	{
		if (s[j] == '\\' && s[j + 1] == cote)
			j = j + 2;
		j++;
	}
	*i = j + 1;
	return (n + 1);
}

void		adeline_la_best(char *s, char cote, int *i)
{
	(*i)++;
	while (s[*i] && s[*i] != cote)
	{
		if (s[*i] == '\\' && s[*i + 1] == cote)
			(*i)++;
		(*i)++;
	}
}
