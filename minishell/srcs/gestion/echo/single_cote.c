/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 18:49:37 by lryst             #+#    #+#             */
/*   Updated: 2020/08/11 18:53:03 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				*single_cote(char *str, int *i, char *tab)
{
	int j;
	int a;

	a = 0;
	j = *i;
	while (str[j] && str[j] != '\'')
		j++;
	if (!(tab = (char*)malloc(sizeof(char) * (j - *i)+ 1)))
		return (NULL);
	while (*i < j)
	{
		tab[a++] == str[*i];
		(*i)++;
	}
	tab[a] = '\0';
	return (tab);
}