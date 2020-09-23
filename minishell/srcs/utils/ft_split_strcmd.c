/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_strcmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 23:18:04 by lryst             #+#    #+#             */
/*   Updated: 2020/09/18 15:27:03 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* #include <unistd.h>
#include <stdlib.h>
#include <stdio.h> */

static int	adeline(char *s, char cote, int n, int *i)
 {
	int j;

	j = *i + 1;
	while (s[j] && s[j] != cote)
	{
		if (s[j] == '\\' && s[j + 1] == cote)
			j = j + 2;
	 	j++;
	}
	*i = j + 1;
	return (n + 1);
 }

 static int			ft_word(char *s, int echo)
{
	int		n;
	int		i;

	i = 0;
	n = 0;
	while (s[i] != '\0')
	{
		printf("ft_word\n");
		printf("char[%d] = [%c]\n", i, s[i]);
		if (s[i] == '"' || s[i] == '\'')
			n = adeline(s, s[i], n, &i);
		if (s[i] == '$')
		{
			printf("dollar\n");
			i++;
			if (s[i] == '?')
			{
				printf("dollar question ?\n");
				i++;
				n++;
			}
			else if (s[i] == '"' || s[i] == '\'')
				n = adeline(s, s[i], n, &i);
			else if (s[i] == ' ' || s[i] == '\0' || s[i] == '\\')
				n++;
			else
			{
				while (s[i] && ((s[i] > 47 && s[i] < 58) || (s[i] > 64 && s[i] < 91) || (s[i] > 96 && s[i] < 123)))
					i++;
				n++;
			}
		}
		if (s[i] == '\\')
		{
			int count;
			int save;

			count = 0;
			save = i;
			while (s[i] && s[i] == '\\')
			{
				i++;
				count++;
			}
			if ((count % 2) == 0)
				n++;
			else if ((count % 2) == 1 && count > 1)
			{
				i--;
				n++;
			}
			if  ((count % 2) == 1 && count > 1 && (s[i + 1] == '\'' || s[i + 1] == '"' || s[i] == '"' || s[i] == '\''))
			{
				i++;
				n++;
			}
			else
			{
				while (s[i] && s[i] != ' ' && s[i] != '"' && s[i] != '\'' && s[i] != '$' && s[i] != '\\')
					i++;
				n++;
			}
		}
		if (s[i] != '\0' && s[i] != ' ' && s[i] != '"' && s[i] != '\'' && s[i] != '$')
		{
			while (s[i] != '\0' && s[i] != ' ' && s[i] != '"' && s[i] != '\'' && s[i] != '\\' && s[i] != '$')
				i++;
			n++;
		}
		if (s[i] == ' ')
		{
			while (s[i] && s[i] == ' ')
				i++;
			if (echo == 1)
				n++;
		}
	}
	return (n);
}

char				*copy(char *s, int *end, int start)
{
	int k;
	char *tab;

	k = 0;
	if (!(tab = (char*)malloc(sizeof(char) * (*end - start) + 1)))
		return NULL;
	while (start < *end)
		tab[k++] = s[start++];
	tab[k] = '\0';
	return (tab);
}

char			*ft_fill(char *s, int echo, int *i, char *tab)
{
	int		save;

	while (s[*i] != '\0')
	{
		printf("		char[%d] = [%c]\n", *i, s[*i]);
		if (s[*i] == '"' || s[*i] == '\'')
		{
			save = *i;
			adeline(s, s[*i], 0, i);
			if (save < *i)
				return (tab = copy(s, i, save));
		}
		if (s[*i] == '$')
		{
			save = *i;
			(*i)++;
			if (s[*i] == '?')
			{
				(*i)++;
				return (tab = copy(s, i, save));
			}
			else if (s[*i] == '"' || s[*i] == '\'')
			{
				adeline(s, s[*i], 0, i);
				if (save < *i)
					return (tab = copy(s, i, save));
			}
			else if (s[*i] == ' ' || s[*i] == '\0' || s[*i] == '\\')
				return (tab = ft_strdup("$\0"));
			else
			{
				while (s[*i] && ((s[*i] > 47 && s[*i] < 58) || (s[*i] > 64 && s[*i] < 91) || (s[*i] > 96 && s[*i] < 123)))
					(*i)++;
				return (tab = copy(s, i, save));
			}
		}
		if (s[*i] == '\\')
		{
			int count;

			count = 0;
			save = *i;
			while (s[*i] && s[*i] == '\\')
			{
				(*i)++;
				count++;
			}
			if ((count % 2) == 0)
				return (tab = copy(s, i, save));
			else if ((count % 2) == 1 && count > 1)
			{
				(*i)--;
				return (tab = copy(s, i, save));
			}
			if  (s[*i + 1] == '\'' || s[*i + 1] == '"' || s[*i] == '"' || s[*i] == '\'')
			{
				(*i)++;
				return (tab = copy(s, i, save));
			}
			else
			{
				while (s[*i] && s[*i] != ' ' && s[*i] != '"' && s[*i] != '\'' && s[*i] != '$' && s[*i] != '\\')
					(*i)++;
				return (tab = copy(s, i, save));
			}
		}
		if (s[*i] != '\0' && s[*i] != ' ' && s[*i] != '"' && s[*i] != '\'' && s[*i] != '$' && s[*i] != '\\')
		{
			save = *i;
			while (s[*i] && s[*i] != ' ' && s[*i] != '"' && s[*i] != '\'' && s[*i] != '$' && s[*i] != '\\')
				(*i)++;
			return (tab = copy(s, i, save));
		}
		if (s[*i] == ' ')
		{
			while (s[*i] && s[*i] == ' ')
				(*i)++;
			if (echo == 1)
				return(tab = ft_strdup(" \0"));
		}
	}
	return NULL;
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
	printf("NBR WORD = %d\n", n);
	if (!(tab = (char **)malloc(sizeof(tab) * (n + 1))))
		return (NULL);
	while (++j < n)
		tab[j] = ft_fill(s, echo, &i, tab[j]);
	tab[j] = 0;
	i = 0;
	while (tab[i])
	{
		printf("tab[%d] = [%s]\n",i,  tab[i]);
		i++;
	}
	return (tab);
}
