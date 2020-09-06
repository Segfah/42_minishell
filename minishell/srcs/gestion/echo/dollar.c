/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 18:51:11 by lryst             #+#    #+#             */
/*   Updated: 2020/08/24 20:46:08 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//put_dollar_variable(check_dollar(str, i, temp->varenv), tab, &k, temp->varenv);

char		*put_dollar_variable(char *str, char *tab)
{
	int i;

	i = 0;
	printf("put_dollar_variable	str[%s]\n", str);
	if (!(tab = ft_strdup(str)))
	{
		if (!(tab = (char*)malloc(sizeof(char) * 2)))
			return NULL;
		while (i < 3)
			tab[i++] = '\0';
	}
	ft_free(str);
	return (tab);
}

char		*check_dollar(char *str, int *i, t_lists *var)
{
	char *tmp;
	int save;
	int j;

	if (str[*i + 1] != '\0')
		(*i)++;
	save = *i;
	j = 0;
	while (str[save] && ((str[save] > 47 && str[save] < 58) || (str[save] > 64 && str[save] < 91) || (str[save] > 96 && str[save] < 123)))
		save++;
	if (!(tmp = (char*)malloc(sizeof(char) * (save - *i) + 1)))
		return (0);
	*i = save;
	while (var)
	{
		if (ft_strcmp(var->name, tmp) == 0)
		{
			return (tmp = ft_strdup(var->data));
		}
		var = var->next;
	}
	return (NULL);
}

int			count_dollar_varriable(char *str, int *j, t_lists *var)
{
	char *variable;
	int ret;
	int count;
	int save;
	int i;

	*j = *j + 1;
	i = 0;
	count = *j;
	save = *j;
	printf("char = [%c]\n", str[*j]);
	printf("j before count variable = %d\n", *j);
	while (str[*j] != '\0' && str[*j] > 64 && str[*j] < 91)
	{
		(*j)++;
		i++;
	}
	count = *j;
	printf("char = [%c]\n", str[*j]);
	if (!(variable = (char*)malloc(sizeof(char) * i + 1)))
		return (0);
	i = 0;
	while (save < *j)
		variable[i++] = str[save++];
	printf("variable = [%s]\n", variable);	
	while (var)
	{
		if (ft_strcmp(var->name, variable) == 0)
		{
			printf("ft_strlen = %zu\n", ft_strlen(var->data));
			ret = ft_strlen(var->data);
			printf("j = %d\n", *j);
			ft_free(variable);
			return (ret);
		}
		var = var->next;
	}
	ft_free(variable);
	return (0);
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