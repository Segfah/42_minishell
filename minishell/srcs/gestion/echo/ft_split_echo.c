/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 23:18:04 by lryst             #+#    #+#             */
/*   Updated: 2020/08/11 20:19:54 by lryst            ###   ########.fr       */
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

 static int			ft_count_word(char *s)
{
	int		n;
	int		i;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		if (s[i] != '\\' && (s[i + 1] == '"' || s[i +1] == '\''))
			n = adeline(s, s[i], n, &i);
		if (s[i] == '\\' && (s[i + 1] == '"' || s[i +1] == '\''))
			n = adeline(s, s[i + 1], n, &i);
		while (s[i] != '\0' && s[i] == ' ')
			i++;
		if (s[i] != '\0' && s[i] != ' ' && s[i] != '"' && s[i] != '\'')
		{
			while (s[i] != '\0' && s[i] != ' ' && s[i] != '"' && s[i] != '\'')
				i++;
			n++;
		}
	}
	return (n);
}

static	char		*remove_cote(char *s, int start, int *end, char cote)
{
	int i;
	char *ret;

	i = *end;
	if (s[start] == cote)
		start++;
	while (start < *end && s[*end] != cote)
		(*end)--;
	if (*end == start)
		*end = i;
	if (!(ret = (char*)malloc(sizeof(char) * (*end - start) + 1)))
		return NULL;
	i = 0;
	while (start < *end)
	{
		ret[i++] = s[start++];
	}
	ret[i]= '\0';
	return (ret);
}

static char			*ft_fill(char *s, int *i, char *tab, t_temp *temp)
{
	int		save;
	int		k;

	k = 0;
	while (s[*i] != '\0')
	{
		if (s[*i] == '\'')
			return (single_cote(s, i + 1, tab));
		else if (s[*i] != '"')
			return (double_cote(s, i + 1, tab, temp));
		else if (s[*i] == '\\')
			return (slash());
		else if (s[*i] == ' ')
			i++;
		else if (s[*i] == '$')
			return (dollar_variable());
		else if (s[*i] != ' ' && s[*i] != '"' && s[*i] != '\'' && s[*i] != '\\' && s[*i] != '$')
			return (word());
		/* else if (s[*i] != '\0' && s[*i] != c && s[*i] != '"' && s[*i] != '\'')
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
					tab[k++] = s[save++];
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
		(*i)++; */
	}
	return NULL;
}

char				**ft_split_echo(char *s, t_temp *temp)
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
	n = ft_count_word(s);
	printf("NBR WORD %d\n", n);
	if (!(tab = (char **)malloc(sizeof(tab) * (n + 1))))
		return (NULL);
	while (++j < n)
		tab[j] = ft_fill(s, &i, tab[j], temp);
	tab[j] = NULL;
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