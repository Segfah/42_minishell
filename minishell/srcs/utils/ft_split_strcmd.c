/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_strcmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:07:21 by lryst             #+#    #+#             */
/*   Updated: 2020/08/04 21:12:05 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static	int					is_cote(char *str, int i)
{
	printf("%c\n", str[i]);
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			i++;
			while (str[i] != '\0' && (str[i] != '\'' || str[i] != '"'))
				i++;
			if (str[i] == '\'' || str[i] == '"')
				return (i);
		}
		i++;
	}
	return (0);
}

static int			ft_word(char *s, char c)
{
	int		n;
	int		i;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		if (is_cote(s, i) != 0)
		{
			printf("				i = %d", i);
			i = is_cote(s, i) + i;
			printf("				i = %d", i);
			n++;
		}
		while (s[i] == c)
			i++;
		s[i] != '\0' ? n++ : 0;
		i++;
	}
	return (n);
}

static char			*ft_fill_cote(char *s,int i, char *tab)
{
	int count;
	int a;

	a = 0;
	count = is_cote(s, i);
	if (!(tab = (char*)malloc(sizeof(char) * (count - i + 1))))
		return (NULL);
	while (i < count)
	{
		tab[a] = s[i];
		i++;
	}
	tab[a] = '\0';
	printf("tab fill_cote = [%s]\n", tab);
	return (tab);
}

static char			*ft_fill(char *s, char c, int i, char *tab)
{
	int		k;
	char	*word;

	k = i;
	while (s[k] != c && s[k] != '\0')
		k++;
	word = (char *)malloc(sizeof(char) * (k + 1));
	if (!word)
		return (NULL);
	k = 0;
	while (s[i] != c && s[i] != '\0')
		word[k++] = s[i++];
	word[k] = '\0';
	tab = word;
	return (tab);
}

char				**ft_split_strcmd(char *s, char c)
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
	n = ft_word(s, c);
	printf("NBR WORD = %d\n", n);
	if (!(tab = (char **)malloc(sizeof(tab) * (n + 1))))
		return (NULL);
	while (++j < n)
	{
		if (is_cote(s, i) != 0)
		{
			printf("			YOLO\n");
			tab[j] = ft_fill_cote(s, i, tab[j]);
			j++;
			i = is_cote(s, i) + i;
		}
		while (s[i] == c)
			i++;
		tab[j] = ft_fill(s, c, i, tab[j]);
		while (s[i] != c && s[i] != '\0')
			i++;
	}
	tab[j] = 0;
	return (tab);
}


int main()
{
	char str1[] = "bonjour les cop1, il m'a dit \"  weshhhh !\" vous en pensez quoi?";
	char str2[] = "bonjour les cop1, il m'a dit : wesh, vous en pesez quoi ?";
	char **tab1;
	char **tab2;
	int i;

	i = 0;
	tab1 = ft_split_strcmd(str1, ' ');
	while (tab1[i] != NULL)
	{
		printf("tab1[%d] = [%s]\n", i, tab1[i]);
		i++;
	}
	i = 0;
	tab2 = ft_split_strcmd(str2, ' ');
	while (tab2[i] != NULL)
	{
		printf("tab2[%d] = [%s]\n", i, tab2[i]);
		i++;
	}
	return (0);
}