/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 23:18:04 by lryst             #+#    #+#             */
/*   Updated: 2020/08/23 16:43:20 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* #include <unistd.h>
#include <stdlib.h>
#include <stdio.h> */

static int          adeline(char *s, char cote, int n, int *i)
 {
	(*i)++;
	while (s[*i] && s[*i] != cote)
	 	(*i)++;
	if (s[*i] && s[*i] == cote)
		(*i)++;
	return (n + 1);
 }

 static int			ft_count_word(char *s, t_lists *var)
{
	int		n;
	int		i;
	int		count;

	i = 0;
	n = 0;
	count = 0;
	while (s[i] != '\0')
	{
		printf("str[%d] 1  = [%c]		n = %d\n", i, s[i], n);
		if (s[i] && s[i] == ' ')
			i++;
		printf("str[%d] 2  = [%c]		n = %d\n", i, s[i], n);
		if (s[i] && (s[i] == '"' || s[i] == '\''))
		{
			printf("\ni == %d\n\n", i);
			n = adeline(s, s[i], n, &i);
			printf("\ni == %d\n\n", i);
		}
		printf("str[%d]  3 = [%c]		n = %d\n", i, s[i], n);
		if (s[i] && s[i] == '\\')
		{
			while (s[i] && s[i] == '\\')
			{
				count++;
				i++;
			}
			printf("			slash char = [%c]\n", s[i]);
			if (s[i] == ' ' || s[i] == '\0' || s[i] == '$')
				n++;
			if (s[i] == '"' || s[i] == '\'')
				n = adeline(s, s[i], n, &i);
		}
		printf("str[%d] 4  = [%c]		n = %d\n", i, s[i], n);
		if (s[i] && s[i] == '$')
		{
			char *tmp;
			int save;
			int j;

			i++;
			save = i;
			j = 0;
			if (s[i + 1] == ' ' || s[i] == '\0')
				n = n + 1;
			while (s[save] != '\0' && ((s[save] > 47 && s[save] < 58) || (s[save] > 64 && s[save] < 91) || (s[save] > 96 && s[save] < 123)))
				save++;
			printf("save = %d\n", save);
			if (!(tmp = (char*)malloc(sizeof(char) * (save - i) + 1)))
				return (0);
			while (i < save)
				tmp[j++] = s[i++];
			tmp[j] = '\0';
			printf("COUNT DOLLAR SPLIT tmp = [%s]\n", tmp);
			n = n + is_it_var(tmp, var);
		}
		printf("str[%d] 5  = [%c]		n = %d\n", i, s[i], n);
		if (s[i] != '\0' && s[i] != '$' && s[i] != '"' && s[i] != '\'' && s[i] != '\\' && s[i] != ' ')
		{
			while (s[i] != '\0' && s[i] != '$' && s[i] != '"' && s[i] != '\'' && s[i] != '\\' && s[i] != ' ')
				i++;
			n++;
		}
		printf("str[%d] 5  = [%c]		n = %d\n", i, s[i], n);
	}
	return (n);
}

char				*remove_cote(char *s, int *start, char cote)
{
	int i;
	char *ret;
	int save;

	if (s[*start] == cote)
		(*start)++;
	save = *start;
	while (s[*start] && s[*start] != cote)
		(*start)++;
	if (!(ret = (char*)malloc(sizeof(char) * (*start - save) + 1)))
		return NULL;
	i = 0;
	while (save < *start)
		ret[i++] = s[save++];
	ret[i]= '\0';
	if (s[*start])
		(*start)++;
	return (ret);
}

static char			*ft_fill(char *s, int *i, char *tab, t_temp *temp)
{
	int		k;
	char 	*tmp;
	k = 0;
	while (s[*i] != '\0')
	{
		printf("start ======>\n");
		printf("char[%d] = [%c]\n", *i, s[*i]);
		if (s[*i] == '\'')
		{
			printf("single cote !\n");
			return (single_cote(remove_cote(s, i, s[*i]), tab));
		}
		else if (s[*i] == '"')
		{
			printf("double cote !\n");
			return (double_cote((remove_cote(s, i, s[*i])), tab, temp->varenv));
		}
		else if (s[*i] == '\\')
		{
			printf("slash !\n");
			return (slash(s, i, tab, temp->varenv));
		}
		else if (s[*i] == '$')
		{
			printf("dollar !\n");
			printf("dollar char = [%c]\n", s[*i]);
			if (s[*i + 1] == ' ' || s[*i + 1] == '\0')
				return (tab = ft_strdup("$\0"));
			if ((tmp = check_dollar(s, i, temp->varenv )) != NULL)
				return (put_dollar_variable(tmp, tab));
			(*i)++;
		}
		else if (s[*i] != ' ' && s[*i] != '"' && s[*i] != '\'' && s[*i] != '\\' && s[*i] != '$')
		{
			printf("word !\n");
			return (word(s, i, tab));
		}
		(*i)++;
	}
	return NULL;
}

char				**ft_split_echo(char *s, int *n, t_temp *temp)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!s)
		return (NULL);
	*n = ft_count_word(s, temp->varenv);
	printf("NBR WORD %d\n", *n);
	if (!(tab = (char **)malloc(sizeof(tab) * (*n + 1))))
		return (NULL);
	while (++j < *n)
	{
		tab[j] = ft_fill(s, &i, tab[j], temp);
	}
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
