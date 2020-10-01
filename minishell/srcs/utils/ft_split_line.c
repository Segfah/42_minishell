/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 14:28:38 by lryst             #+#    #+#             */
/*   Updated: 2020/10/01 16:37:36 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		adeline_la_best(char *s, char cote, int *i)
{
	int j;

	j = *i + 1;
	while (s[j] && s[j] != cote)
	{
		if (s[j] == '\\' && s[j + 1] == cote)
			j++;
		j++;
	}
	if (s[j] != '\0')
		*i = j + 1;
	return ;
}

int				ft_count_word(char *str)
{
	int word;
	int i;
	int slash;

	word = 0;
	slash = 0;
	i = 0;
	if (str)
		word = 1;
	while (str[i])
	{
		count_slash(str, &i);
		if (str[i] == '"' || str[i] == '\'')
			adeline_la_best(str, str[i], &i);
		if (str[i] == ';')
			word++;
		i++;
	}
	return (word);
}

char			*ft_fill_line(char *str, int *i, char *tab)
{
	int save;
	int slash;

	save = *i;
	slash = 0;
	while (str[*i])
	{
		count_slash(str, i);
		if (str[*i] == '"' || str[*i] == '\'')
			adeline_la_best(str, str[*i], i);
		if (str[*i] == ';' || str[*i] == '\0')
		{
			tab = copy(str, i, save);
			if (str[*i + 1] != '\0')
				(*i)++;
			return (tab);
		}
		(*i)++;
	}
	if (str)
		return (tab = copy(str, i, save));
	return NULL;
}

int				multi_pv(char *str)
{
	int i;
	int slash;
	int check;

	i = 0;
	slash = 0;
	check = 0;
	while (str[i])
	{
		count_slash(str, &i);
		if (str[i] == '\'' || str[i] == '"')
			adeline_la_best(str, str[i], &i);
		if (str[i] == ';' && str[i + 1] == ';')
		{
			write(1, "minishell: syntax error near unexpected token ';;'\n", 51);
			return (0);
		}
		if (str[i + 1] && str[i] == ';')
		{
			i++;
			while (str[i] && str[i] == ' ')
				i++;
			if (str[i] == ';')
			{
				write(1, "minishell: syntax error near unexpected token ';'\n", 50);
				return (0);
			}
		}
		else if (str[i])
			i++;
	}
	return (1);
}

char			**ft_split_line(char *str)
{
	char **tab;
	int i;
	int j;
	int word;

	i = 0;
	j = -1;
	word = 0;
	tab = NULL;
	if (!str)
		return NULL;
	if (!(multi_pv(str)))
	{
		if (!(tab = malloc(sizeof(char*) * 1)))
			return (NULL);
		tab[0] = NULL;
		return (tab);
	}
	word = ft_count_word(str);
	if (!(tab = (char **)malloc(sizeof(char*) * (word + 1))))
		return NULL;
	while (++j < word)
	{
		while (str[i] && str[i] == ' ')
			i++;
		tab[j] = ft_fill_line(str, &i, tab[j]);
	}
	tab[j] = 0;
	j = -1;
	while(tab[++j])
		printf("lineTAB[%d] = {%s]\n", j, tab[j]);
	return (tab);
}
