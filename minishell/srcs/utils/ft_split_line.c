/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 14:28:38 by lryst             #+#    #+#             */
/*   Updated: 2020/10/19 15:02:38 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_count_word(char *str)
{
	int word;
	int i;

	word = 0;
	i = 0;
	if (str)
		word = 1;
	while (str[i])
	{
		count_slash(str, &i);
		if (str[i] == '"' || str[i] == '\'')
			adeline_la_best(str, str[i], &i);
		else if (str[i] == ';')
			word++;
		i++;
	}
	return (word);
}

char			*ft_fill_line(char *str, int *i, char *tab)
{
	int save;

	save = *i;
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
	return (NULL);
}

char			**ft_split_line(char *str)
{
	char	**tab;
	int		i;
	int		j;
	int		word;

	i = 0;
	j = -1;
	word = 0;
	tab = NULL;
	if (!str)
		return (NULL);
	if (!(multi_pv(str, 0)))
		return (tab_null(tab));
	word = ft_count_word(str);
	if (!(tab = (char **)malloc(sizeof(char*) * (word + 1))))
		return (NULL);
	while (++j < word)
	{
		while (str[i] && (str[i] == ' ' || str[i] == '\t'))
			i++;
		tab[j] = ft_fill_line(str, &i, tab[j]);
	}
	tab[j] = 0;
	return (tab);
}
