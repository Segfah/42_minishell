/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/03 20:01:27 by lryst             #+#    #+#             */
/*   Updated: 2020/10/27 14:14:40 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				*copy(char *s, int *end, int start)
{
	int		k;
	char	*tab;

	k = 0;
	if (!(tab = (char*)malloc(sizeof(char) * (*end - start) + 1)))
		return (NULL);
	while (start < *end)
		tab[k++] = s[start++];
	tab[k] = '\0';
	return (tab);
}

char				*copy_slash_m(char *s, int *i, char *tab, int save)
{
	(*i)--;
	return (tab = copy(s, i, save));
}

char				*copy_slash_p(char *s, int *i, char *tab, int save)
{
	(*i)++;
	return (tab = copy(s, i, save));
}

char				*copy_adeline(char *s, int *i, char *tab)
{
	int save;

	save = *i;
	adeline(s, s[*i], 0, i);
	return (tab = copy(s, i, save));
}

char				*copy_adeline2(char *s, int *i, char *tab)
{
	int save;

	save = *i;
	adeline2(s, s[*i], 0, i);
	return (tab = copy(s, i, save));
}
