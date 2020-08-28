/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_cote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 18:49:57 by lryst             #+#    #+#             */
/*   Updated: 2020/08/11 20:54:07 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* 
static	void		count_dollar_varriable(char *str, int *j, t_temp *temp)
{
	char *variable;

	if (str[*j] == '$' && str[*j + 1] != ' ')
	{

	}
	(*j)++;
} */

static	char		*dollar_with_variable(char *str, int *i)
{
	char *variable;

	return (variable);
	return NULL;
}

static	char		*put_in_tab(char *str, int *i, char *tab, int j)
{
	int slash;
	int k;
	int l;
	char *variable;

	k = 0;
	l = 0;
	slash = 0;
	if (!(tab = (char*)malloc(sizeof(char) * j + 1)))
		return NULL;
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '\\')
		{
			l = 0;
			slash = count_slash(str, i);
			while (l++ < slash)
				tab[k++] = '\\';
		}
		if (str[*i] == '$' && (variable = dollar_with_variable(str, i) != NULL))
		{
			
		}
		else if (str[*i] != '\\')
			tab[k++] = str[(*i)++];
	}
}

char				*double_cote(char *str, int *i, char *tab, t_temp *temp)
{
	int j;
	int a;
	int slash;

	j = *i;
	a = 0;
	slash = 0;
	while (str[j] && str[j] != '"')
	{
		if (str[j] == '\\')
			slash = slash + count_slash(str, &j);
		if (str[j] == '$' )
			count_dollar_varriable(str, &j, temp);
		j++;
	}
	j = j - slash;
	return (put_in_tab(str, i, tab, j));	
}