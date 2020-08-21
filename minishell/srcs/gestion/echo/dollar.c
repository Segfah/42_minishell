/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 18:51:11 by lryst             #+#    #+#             */
/*   Updated: 2020/08/17 16:58:13 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//put_dollar_variable(check_dollar(str, i, temp->varenv), tab, &k, temp->varenv);

char		*put_dollar_variable(char *str, char *tab)
{
	int i;

	i = 0;
	if (!(tab = ft_strdup(str)))
	{
		if (!(tab = (char*)malloc(sizeof(char) * 2)))
		while (i < 3)
			tab[i] = '\0';
	}
	ft_free(str);
	return (tab);
}

char		*check_dollar(char *str, int *i, t_lists *var)
{
	char *tmp;
	int save;
	int j;

	printf("check dollar : char = [%c]\n", str[*i]);
	if (str[*i + 1] != '\0')
		(*i)++;
	save = *i;
	j = 0;
	while (str[save] && ((str[save] > 47 && str[save] < 58) || (str[save] > 64 && str[save] < 91) || (str[save] > 96 && str[save] < 123)))
		save++;
	if (!(tmp = (char*)malloc(sizeof(char) * (save - *i) + 1)))
		return (0);
	while (*i < save)
		tmp[j++] = str[(*i)++];
	tmp[j] = '\0';
	printf("	tmp = [%s]\n", tmp);
	while (var)
	{
		if (ft_strcmp(var->name, tmp) == 0)
			return (tmp = ft_strdup(var->data));
		var = var->next;
	}
	return (NULL);
}

void		count_dollar_varriable(char *str, int *j, t_lists *var)
{
	char *variable;
	int count;
	int i;

	*j = *j + 1;
	count = *j;
	i = 0;
	while (str[count] > 64 && str[count] < 91)
	{
		count++;
		i++;
	}
	if (!(variable = (char*)malloc(sizeof(char)* i + 1)))
		return ;
	i = 0;
	while (*j < count)
		variable[i++] = str[(*j)++];		
	while (var)
	{
		if (ft_strcmp(var->name, variable) == 0)
		{
			*j = count;
			ft_free(variable);
			return ;
		}
		var = var->next;
	}
	return ;
}

int		is_it_var(char *str, t_lists *var)
{
	while (var)
	{
		if (ft_strcmp(var->name, str) == 0)
		{
			ft_free(str);
			return (1);
		}
		var = var->next;
	}
	return (0);
}