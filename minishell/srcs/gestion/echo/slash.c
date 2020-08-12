/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 18:50:48 by lryst             #+#    #+#             */
/*   Updated: 2020/08/12 22:29:59 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					count_slash(char *str, int *j)
{
	int ret;

	ret = 0;
	while (str[*j] && str[(*j)++] == '\\')
		ret++;
	ret = ret / 2;
	if (str[*j])
		(*j)++;
	return (ret);
}

char				*remove_slash(char *str, int *i, char save)
{
	char *ret; 
	int count;
	int j;

	j = *i;
	count = 0;
	while (str[(*i)++] != save)
		count++;
	if (!(ret = (char*)malloc(sizeof(char) * count)))
		return NULL;
	while (j< *i - 1)
		ret[count++] = str[j++];
	ret[count] = '\0';
	return (ret);
}

char				*slash_sort(char *str, int *i, char *tab, t_lists *var)
{
	int k;
	char save;

	k = 0;
	save = str[*i];
	if (str[*i] == '"' || str[*i] == '\'')
	{
		tab = double_cote(remove_slash(str, i, save), tab, var);
	}
	return (tab);
}

char				*slash(char *str, int *i, char *tab, t_lists *var)
{
	int slash;
	int k;

	k = 0;
	slash = count_slash(str, i);
	if (!((slash = count_slash(str, i) % 2) == 1))
		return (slash_sort(str, i, tab, var));
	if (!(tab = (char*)malloc(sizeof(char) * slash + 1)))
		return NULL;
	while (tab[k++])
		tab[k] = '\\';
	tab[k] = '\0';
	return (tab);
}
