/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 18:49:37 by lryst             #+#    #+#             */
/*   Updated: 2020/08/24 18:46:17 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				*single_cote(char *str, char *tab)
{
	tab = ft_strdup(str);
	return (tab);
}

char	*put_in_tab_single(char *str, int *i, char *tab, int j, t_lists *var)
{
	int slash;
	int k;
	int l;

	k = 0;
	l = 0;
	slash = 0;
	if (!(tab = (char*)malloc(sizeof(char) * j + 1)))
		return NULL;
	while (str[*i])
	{
		if (str[*i] == '\\')
		{
			l = 0;
			slash = count_slash(str, i);
			while (l++ < slash)
				tab[k++] = '\\';
		}
		if (str[*i] == '$')
			put_dollar_variable(check_dollar(str, i, var), tab);
		tab[k++] = str[(*i)++];
	}
	return (tab);
}

char	*single_keep_cote(char *str, int *i, char *tab, t_lists *var)
{
	int j;
	int save;
	int tmp;
	int slash;

	slash = 0;
	//str = remove_cote(str, i, s[*i + 1]);
	j = *i;
	save = *i;
	while (str[j])
	{
		if (str[j] == '\\')
			slash = slash + count_slash(str, &j);
		if (str[j] == '$')
			tmp = count_dollar_varriable(str, &j, var);
		else if (str[j] != '\\' && str[j] == '$')
			j++;
	}
	*i = save;
	j = j - slash - save;
	return (put_in_tab_single(str, i, tab, j, var));	
}