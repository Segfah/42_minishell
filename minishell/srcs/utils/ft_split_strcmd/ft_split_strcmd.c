/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_strcmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 23:18:04 by lryst             #+#    #+#             */
/*   Updated: 2020/11/19 12:27:09 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			ft_word(char *s, int echo)
{
	int		n;
	int		i;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '>' || s[i] == '<' || s[i] == '|')
			n = adeline2(s, s[i], n, &i);
		if (s[i] == '"' || s[i] == '\'')
			n = adeline(s, s[i], n, &i);
		if (s[i] == '$')
			ft_count_word_dollar(s, &i, &n);
		if (s[i] == '\\')
			ft_count_word_slash(s, &i, &n);
		if (s[i] != '\0' && s[i] != ' ' && s[i] != '\t' && s[i] != '"' &&
		s[i] != '\'' && s[i] != '$' && s[i] != '>' &&
		s[i] != '<' && s[i] != '|')
			ft_count_word_char(s, &i, &n);
		if (s[i] == ' ' || s[i] == '\t')
			ft_count_word_space(s, &i, &n, &echo);
	}
	return (n);
}

char				*ft_fill(char *s, int echo, int *i, char *tab)
{
	while (s[*i] != '\0')
	{
		if (s[*i] == '>' || s[*i] == '<' || s[*i] == '|')
			return (copy_adeline2(s, i, tab));
		if (s[*i] == '"' || s[*i] == '\'')
			return (copy_adeline(s, i, tab));
		if (s[*i] == '$')
			return (ft_fill_dollar(s, i, tab));
		if (s[*i] == '\\')
			return (ft_fill_slash(s, i, tab));
		if (s[*i] != '\0' && s[*i] != ' ' && s[*i] != '\t' && s[*i] != '"' &&
		s[*i] != '\'' && s[*i] != '$' && s[*i] != '\\' && s[*i] != '>' &&
		s[*i] != '<' && s[*i] != '|')
			return (ft_fill_char(s, i, tab));
		if (s[*i] == ' ' || s[*i] == '\t')
		{
			while (s[*i] && (s[*i] == ' ' || s[*i] == '\t'))
				(*i)++;
			if (echo == 1)
				return (tab = ft_strdup(" \0"));
		}
	}
	return (NULL);
}

char				**ft_split_strcmd(char *s, int echo)
{
	char	**tab;
	int		i;
	int		n;
	int		j;

	i = 0;
	n = 0;
	j = -1;
	if (!s)
		return (NULL);
	n = ft_word(s, echo);
	if (!(tab = (char **)malloc(sizeof(tab) * (n + 1))))
		return (NULL);
	while (++j < n)
		tab[j] = ft_fill(s, echo, &i, tab[j]);
	tab[j] = 0;
	return (tab);
}
