/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 14:28:38 by lryst             #+#    #+#             */
/*   Updated: 2020/09/10 18:29:30 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			 adeline_la_best(char *s, char cote, int *i)
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

int					ft_count_word(char *str)
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
		if (str[i] == '\\')
		{
			while (str[i] && str[i] == '\\')
			{
				slash++;
				i++;
			}
			if ((slash % 2) == 1 && (str[i] == '"' || str[i] == '\''))
				i++;
		}
		if (str[i] == '"' || str[i] == '\'')
			adeline_la_best(str, str[i], &i);
		if (str[i] == ';')
			word++;
		i++;
	}
	return (word);
}

char				*ft_fill_line(char *str, int *i, char *tab)
{
	int save;
	int slash;

	save = *i;
	slash = 0;
	printf("i = %d\n", *i);
	while (str[*i])
	{
		if (str[*i] == '\\')
		{
			while (str[*i] && str[*i] == '\\')
			{
				slash++;
				(*i)++;
			}
			if ((slash % 2) == 1 && (str[*i] == '"' || str[*i] == '\''))
				(*i)++;
		}
		if (str[*i] == '"' || str[*i] == '\'')
		{
			adeline_la_best(str, str[*i], i);
		}
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
		return (tab = ft_strdup(str));
	return NULL;
}

char				**ft_split_line(char *str)
{
	char **tab;
	int i;
	int j;
	int word;

	i = 0;
	j = -1;
	word = 0;
	if (!str)
		return NULL;
	word = ft_count_word(str);
	printf("NBR WORD = %d\n", word);
	if (!(tab = (char **)malloc(sizeof(char*) * (word + 1))))
		return NULL;
	while (++j < word)
	{
		while (str[i] && str[i] == ' ')
			i++;
		tab[j] = ft_fill_line(str, &i, tab[j]);
		printf("TABLINE = [%s]\n", tab[j]);
	}
	tab[j] = 0;
	return (tab);
}
