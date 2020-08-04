/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 04:16:15 by corozco           #+#    #+#             */
/*   Updated: 2020/08/04 04:17:49 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** cherche s'il y a une ou plusieres " o ' et return le nombre des espaces
** que la clean_str doit garder
*/

static int		single_or_double_quote(char *str, int i, char c)
{
	int			k;

	k = 1;
	while (str[++i])
	{
		if (str[i] == c)
			return (k + 1);
		k++;
	}
	return (0);
}

/*
** fonction qui trouve un " ou un ' et active le flag correspondant
*/

static void		skyp_spaces(char *str, int j, int *k)
{
	int			flag34;
	int			flag39;

	flag34 = 0;
	flag39 = 0;
	if (str[j] == 34 || str[j] == 39)
	{
		if (str[j] == 34)
			flag34 = (flag34 == 0) ? 1 : 0;
		else
			flag39 = (flag39 == 0) ? 1 : 0;
		if (flag34 == 1 || flag39 == 1)
			*k = single_or_double_quote(str, j, str[j]);
	}
}

/*
** Cette fonction efface les espaces et les \t
*/

void			clean_str(char *str)
{
	int			i;
	int			j;
	int			k;

	j = 0;
	k = 0;
	while (str[j] == ' ' || str[j] == '\t')
		j++;
	i = 0;
	while (str[j])
	{
		skyp_spaces(str, j, &k);
		if ((str[j] != ' ' || str[j + 1] != ' ') && k == 0)
			str[i++] = str[j];
		if (k > 0)
		{
			str[i++] = str[j];
			k--;
		}
		j++;
	}
	str[i] = 0;
	while (str[--i] == ' ' || str[i] == '\t')
		str[i] = 0;
}
