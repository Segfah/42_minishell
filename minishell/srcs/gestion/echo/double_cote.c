/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_cote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 18:49:57 by lryst             #+#    #+#             */
/*   Updated: 2020/08/24 19:46:22 by lryst            ###   ########.fr       */
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
			printf("put_in_tab_double TMP = [%s]\n", tmp);
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
	int save;
	int slash;
	int tmp;

	slash = 0;
	//str = remove_cote(str, i, s[*i + 1]);
	j = 0;
	tmp = 0;
	printf("double_cote str = [%s]\n", str);
	while (str[j] != '\0')
	{
		if (str[j] != '\0' && str[j] != '\\' && str[j] != '$')
			j++;
		printf("str [%d] = %c\n",j, str[j]);
		if (str[j] != '\0' && str[j] == '\\')
		{
			printf("WESHHHH !\n");
			slash = slash + count_slash(str, &j);
		}
		if (str[j] != '\0' && str[j] == '$')
		{
			tmp = j;
			save = count_dollar_varriable(str, &j, var);
			printf("SAVE = %d\n", save);
			printf("			ok [%c]\n", str[j]);
			while(str[tmp] && str[tmp] > 64 && str[tmp] < 91)
				tmp++;
		}
	}
	printf("slash = %d\n", slash);
	j = j - slash + save - tmp;
	printf("size = %d\n", j);
	return (put_in_tab_double(str, tab, j, var));	
}
