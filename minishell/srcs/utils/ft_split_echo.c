/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 23:18:04 by lryst             #+#    #+#             */
/*   Updated: 2020/08/06 00:36:09 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* #include <unistd.h>
#include <stdlib.h>
#include <stdio.h> */

static int          adeline(char *s, char cote, int n, int *i)
 {
	int j;

	j = *i + 1;
	while (s[j] && s[j] != cote)
	 	j++;
	*i = j + 1;
	return (n + 1);
 }

 static int			ft_word(char *s, char c)
{
	int		n;
	int		i;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == '\'')
			n = adeline(s, s[i], n, &i);
		while (s[i] != '\0' && s[i] == c)
			i++;
		if (s[i] != '\0' && s[i] != c && s[i] != '"' && s[i] != '\'')
		{
			while (s[i] != '\0' && s[i] != c && s[i] != '"' && s[i] != '\'')
				i++;
			n++;
		}
	}
	return (n);
}

static char			*ft_fill(char *s, char c, int *i, char *tab)
{
	int		save;
	int		k;

	k = 0;
	while (s[*i] != '\0')
	{
		if (s[*i] == '"' || s[*i] == '\'')
		{
			save = *i;
			adeline(s, s[*i], 0, i);
			if (save < *i)
			{
				k = 0;
				if (!(tab = (char*)malloc(sizeof(char) * (*i - save) + 1)))
					return NULL;
				while (*i > save)
					tab[k++] = s[save++];
				tab[k] = '\0';
				return (tab);
			}
		}
		else if (s[*i] != '\0' && s[*i] != c && s[*i] != '"' && s[*i] != '\'')
		{
			save = *i;
			k = 0;
			while (s[*i] != '\0' && s[*i] != c && s[*i] != '"' && s[*i] != '\'')
				(*i)++;
			if (s[*i] != '"' && s[*i] != '\'')
			{
				if (s[*i] == c)
					(*i)++;
				if (!(tab = (char*)malloc(sizeof(char) * (*i - save) + 1)))
					return NULL;
				while (*i > save)
				{
					tab[k++] = s[save++];
				}
				tab[k] = '\0';
				return (tab);
			}
			if (s[*i] == '"' || s[*i] == '\'')
			{
				if (!(tab = (char*)malloc(sizeof(char) * (*i - save) + 1)))
					return NULL;
				while (*i > save)
					tab[k++] = s[save++];
				tab[k] = '\0';
				return (tab);
			}
		}
		(*i)++;
	}
	return NULL;
}

char				**ft_split_echo(char *s, char c)
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
	if (!(tab = (char **)malloc(sizeof(tab) * (n + 1))))
		return (NULL);
	while (++j < n)
	{
		tab[j] = ft_fill(s, c, &i, tab[j]);
		// while (s[i] != c && s[i] != '\0')
		// 	i++;
	}
	tab[j] = 0;
	return (tab);
}

/* int main()
{
	char *str1 = "bonjour les cop1, il ma dit \"          \' c\' wesh\"";
	char *str3 = "h\"wesh\"";
	char *str2 = "bonjour les cop1, il ma dit : wesh, vous en pesez quoi ?";
	char **tab1;
	char **tab2;
	char **tab3;
	int i;

	i = 0;
	printf("------------ STR1 ------------\n");
	tab1 = ft_split_strcmd(str1, ' ');
	while (tab1[i] != NULL)
	{
		printf("tab1[%d] = [%s]\n", i, tab1[i]);
		i++;
	}
	printf("------------ STR2 ------------\n");
	i = 0;
	tab2 = ft_split_strcmd(str2, ' ');
	while (tab2[i] != NULL)
	{
		printf("tab2[%d] = [%s]\n", i, tab2[i]);
		i++;
	}
	printf("------------ STR3 ------------\n");
	i = 0;
	tab3 = ft_split_strcmd(str3, ' ');
	while ((tab3[i] != NULL))
	{
		printf("tab3[%d] = [%s]\n", i, tab3[i]);
		i++;
	}
	return (0);
} */
