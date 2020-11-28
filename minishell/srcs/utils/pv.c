/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pv.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 20:49:55 by lryst             #+#    #+#             */
/*   Updated: 2020/11/27 18:23:07 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				message_error_pv(int pv)
{
	if (pv == 1)
		write(2, "minishell: syntax error near unexpected token ';'\n", 50);
	if (pv == 2)
		write(2, "minishell: syntax error near unexpected token ';;'\n", 51);
	g_ret = 258;
	return (0);
}

int				truc(char *str, int *i)
{
	if (str[*i + 1])
	{
		(*i)++;
		while (str[*i] && (str[*i] == ' ' || str[*i] == '\t'))
			(*i)++;
		if (str[*i] && str[*i] == ';')
		{
			if (str[*i + 1] && str[*i + 1] == ';')
				return (message_error_pv(2));
			return (message_error_pv(1));
		}
	}
	return (1);
}

int				multi_pv(char *str, int i)
{
	if (ft_strcmp(";", str) == 0)
		return (message_error_pv(1));
	while (str[i])
	{
		count_slash(str, &i);
		if (str[i] == '\'' || str[i] == '"')
			adeline_la_best(str, str[i], &i);
		if (str[i] == ';' && str[i + 1] == ';')
			return (message_error_pv(2));
		if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			return (truc(str, &i));
		if (str[i + 1] && str[i] == ';')
		{
			i++;
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
			if (str[i] == ';')
				return (message_error_pv(1));
		}
		else if (str[i])
			i++;
	}
	return (1);
}

char			**tab_null(char **tab)
{
	if (!(tab = malloc(sizeof(char*) * 1)))
		return (NULL);
	tab[0] = NULL;
	return (tab);
}
