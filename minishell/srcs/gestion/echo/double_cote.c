/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_cote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 18:49:57 by lryst             #+#    #+#             */
/*   Updated: 2020/08/23 17:02:18 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*put_in_tab_double(char *str, char *tab, int j, t_lists *var)
{
	int slash;
	char *tmp;
	int i;
	int k;
	int l;

	k = 0;
	l = 0;
	slash = 0;
	i = 0;
	if (!(tab = (char*)malloc(sizeof(char) * j + 1)))
		return NULL;
	while (str[i])
	{
		if (str[i] == '\\')
		{
			l = 0;
			slash = count_slash(str, &i);
			while (l++ < slash)
				tab[k++] = '\\';
		}
		if (str[i] == '$')
		{
			tmp = put_dollar_variable(check_dollar(str, &i, var), tab);
			l = 0;
			while (tmp[l])
				tab[k++] = tmp[l++];
			free(tmp);
		}
		tab[k++] = str[i++];
	}
	return (tab);
}

char	*double_cote(char *str, char *tab, t_lists *var)
{
	int j;
	int slash;

	slash = 0;
	//str = remove_cote(str, i, s[*i + 1]);
	j = 0;
	while (str[j])
	{
		//printf("%c\n",str[j]);
		if (str[j] == '\\')
		{
			slash = slash + count_slash(str, &j);
		}
		if (str[j] == '$')
			count_dollar_varriable(str, &j, var);
		else if (str[j] != '\\' && str[j] != '$')
			j++;
	}
	j = j - slash;
	return (put_in_tab_double(str, tab, j, var));	
}