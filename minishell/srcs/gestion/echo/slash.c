/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 18:50:48 by lryst             #+#    #+#             */
/*   Updated: 2020/08/23 17:02:49 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					count_slash(char *str, int *j)
{
	int ret;

	ret = 0;
	while (str[*j] && str[(*j)] == '\\')
	{
		(*j)++;
		ret++;
	}
	if (ret == 1)
		return(1);
	ret = ret / 2;	
	return (ret);
}

char				*remove_slash(char *str, int *i, char save)
{
	char *ret; 
	int count;
	int j;

	j = *i;
	count = 0;
	while (str[++(*i)] != save)
		count++;
	if (!(ret = (char*)malloc(sizeof(char) * count)))
		return NULL;
	count = 0;
	while (j < *i - 1)
		ret[count++] = str[j++];
	ret[count] = save;
		count++;
	ret[count] = '\0';
	printf("\n\nret = [%s]\n", ret);
	return (ret);
}

char				*slash_sort(char *str, int *i, char *tab, t_lists *var)
{
	int k;
	char save;

	k = 0;
	save = str[*i];
	if (str[*i] == '"' || str[*i] == '\'')
	{
		tab = double_cote(remove_slash(str, i, save), tab, var);
	}
	printf("	tab = [%s]\n", tab);
	return (tab);
}

char				*slash(char *str, int *i, char *tab, t_lists *var)
{
	int slash;
	int k;
	int l;
	int	save;
	char *tmp;

	k = 0;
	l = 0;
	save = *i;
	slash = -1;
	while (str[++save] == '\\')
	{
		++slash;
	}
	if ((slash % 2) == 1 && (str[save] == '"' || str[save] == '\''))
	{
		printf("impair SLASH ET COTE\n");
		slash = count_slash(str, i);
		tmp = slash_sort(str, i, tab, var);
		if (!(tab = (char*)malloc(sizeof(char) * slash + ft_strlen(tmp) + 1)))
			return NULL;
		while (k < slash)
			tab[k++] = '\\';
		while (tmp[l] != '\0')
			tab[k++] = tmp[l++];
		tab[k] = '\0';
		ft_free(tmp);
		return (tab);
	}
	if ((slash % 2) == 1 && str[save] == '$')
	{
		printf("impair SLASH AND DOLLAR\n");
		int u;

		u = 0;
		slash = count_slash(str, i);
		save++;
		while (str[save] && str[save] != ' ' && str[save] != '"' && str[save] != '\'' && str[save] != '\\')
		{
			u++;
			save++;
		}
		if (!(tab = (char*)malloc(sizeof(char) * (u + slash) + 1)))
			return NULL;
		while (k < slash)
			tab[k++] = '\\';
		while (*i < save)
			tab[k++] = str[(*i)++];
		tab[k] = '\0';
		return (tab);
	}
	slash = count_slash(str, i);
	if (str[*i] == ' ' || str[*i] == '\0')
	{
		printf("SLASH ONLY\n");
		if (!(tab = (char*)malloc(sizeof(char) * slash + 1)))
			return NULL;
		while (k < slash)
			tab[k++] = '\\';
		tab[k] = ' ';
		k++;
		tab[k] = '\0';
		return (tab);
	}
	if (str[*i] == '$')
	{
		printf("pair SLASH AND DOLLAR\n");
		if ((tmp = check_dollar(str, i, var)) != NULL)
		{
			tmp = (put_dollar_variable(tmp, tab));
			if (!(tab = (char*)malloc(sizeof(char) * slash + ft_strlen(tmp) + 1)))
				return NULL;
		}
		else if (!(tmp))
			if (!(tab = (char*)malloc(sizeof(char) * slash + 1)))
				return NULL;
		while (k < slash)
			tab[k++] = '\\';
		if (tmp != NULL)
		{
			while (tmp[l] != '\0')
				tab[k++] = tmp[l++];
			ft_free(tmp);
		}
		tab[k] = '\0';
		return (tab);
	}
	if (str[*i] == '\'' || str[*i] == '"')
	{
		printf("impair SLASH ET COTE\n");
		if (str[*i] == '\'')
			tmp = single_cote(remove_cote(str, i, str[*i]), tab);
		if (str[*i] == '"')
			tmp = double_cote((remove_cote(str, i, str[*i])), tab, var);
		if (!(tab = (char*)malloc(sizeof(char) * slash + ft_strlen(tmp) + 1)))
			return NULL;
		while (k < slash)
			tab[k++] = '\\';
		while (tmp[l] != '\0')
			tab[k++] = tmp[l++];
		tab[k] = '\0';
		ft_free(tmp);
		return (tab);
	}
	if (str[*i] != '\0')
	{
		printf("SLASH AND WORD\n");
		tmp = word(str, i, tab);
		if (!(tab = (char*)malloc(sizeof(char) * slash + ft_strlen(tmp) + 1)))
			return NULL;
		while (k < slash)
			tab[k++] = '\\';
		while (tmp[l] != '\0')
			tab[k++] = tmp[l++];
		tab[k] = '\0';
		ft_free(tmp);
		return (tab);
	}
	return NULL;
}
