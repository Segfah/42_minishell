/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 18:51:11 by lryst             #+#    #+#             */
/*   Updated: 2020/08/12 23:01:57 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//put_dollar_variable(check_dollar(str, i, temp->varenv), tab, &k, temp->varenv);

char		*put_dollar_variable(char *str, char *tab)
{
	if (!(tab = ft_strdup(str)))
		return NULL;
	ft_free(str);
	return (tab);
}

char		*check_dollar(char *str, int *i, t_lists *var)
{
	char *variable;
	char *ret;
	int size;
	int count;

	*i = *i + 1;
	size = *i;
	count = 0;
	while (str[size] > 64 && str[size] < 91)
		size++;
	if (!(variable = (char*)malloc(sizeof(char)* size + 1)))
		return NULL;
	while (count < size)
		variable[count++] = str[(*i)++];
	variable[count] = '\0';
	while (var)
	{
		if (ft_strcmp(var->name, variable) == 0)
		{
			return (ret = ft_strdup(var->data));
		}
		var = var->next;
	}
	return NULL;

}

void		count_dollar_varriable(char *str, int *j, t_lists *var)
{
	char *variable;
	int count;
	int i;

	//*j = *j + 1;
	count = *j;
	i = 0;
	printf("str[%d] = [%c]\n", *j, str[*j]);
	while (str[count++] > 64 && str[count] < 91)
		i++;
	if (!(variable = (char*)malloc(sizeof(char)* i + 1)))
		return ;
	i = 0;
	while ((*j)++ < count)
		variable[i++] = str[*j];		
	printf("variable = [%s]\n", variable);
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
