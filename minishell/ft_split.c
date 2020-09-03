/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 04:05:39 by corozco           #+#    #+#             */
/*   Updated: 2020/09/03 19:05:22 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** #include "libft.h"
**/
#include <stdlib.h>

void		ft_free_split(char **split, int i)
{
	while (i >= 0)
	{
		free(split[i]);
		i--;
	}
	free(split);
	split = NULL;
}

static int	is_split(char s, char c)
{
	if (s == c)
		return (1);
	if (s == '\0')
		return (1);
	return (0);
}

static int	ft_counter(char *str, char c)
{
	int		i;
	int		word;
	int		f34;
	int		f39;

	word = 0;
	i = 0;
	f34 = 0;
	f39 = 0;
	while (str[i] != '\0')
	{
		f34 = (str[i] == 34 && !f39) ? !f34 : f34;
		f39 = (str[i] == 39 && !f34) ? !f39 : f39;
		if (((is_split(str[i + 1], c) == 1 && (!f34 && !f39))
				&& is_split(str[i], c) == 0) || !str[i + 1])
			word++;
		i++;
	}
	return (word);
}

/*
** printf("from [%s]\n",from);
** printf("f34[%d] f39[%d] caractaire[%c]\n",f34, f39,from[i]);
*/

static void		ft_cytab(char *dest, char *from, int f34, int f39)
{
	int		i;
	char	c;

	c = ';';
	i = 0;
	while ((is_split(from[i], c) == 0 || ((is_split(from[i], c)
		&& (f34 || f39)))) && from[i])
	{
		f34 = (from[i] == 34 && !f39) ? !f34 : f34;
		f39 = (from[i] == 39 && !f34) ? !f39 : f39;
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

void			len_malloc(char *str, int *j, int *f34, int *f39)
{

	while (str[*j] && (is_split(str[*j], ';') == 0
		|| (is_split(str[*j], ';') == 1 && (*f34 || *f39))))
	{
		*f39 = (str[++(*j)] == 39 && !(*f34)) ? !(*f39) : *f39;
		*f34 = (str[*j] == 34 && !(*f39)) ? !(*f34) : *f34;
	}
}

static void		ft_writing(char **split, char *str, int f34, int f39)
{
	int		i;
	int		j;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		f34 = (str[i] == 34 && !f39) ? !f34 : f34;
		f39 = (str[i] == 39 && !f34) ? !f39 : f39;
		if (is_split(str[i], ';') == 1 && f34 == 0 && f39 == 0)
			i++;
		else if (!(j = 0))
		{
			len_malloc(&str[i], &j, &f34, &f39);
			if (!(split[word] = (char*)malloc(sizeof(char) * (j + 1))))
			{
				ft_free_split(split, word);
				return ;
			}
			ft_cytab(split[word++], str + i, 0, 0);
			i += j;
		}
	}
}

/*
static void		ft_writing(char **split, char *str, int f34, int f39)
{
	int		i;
	int		j;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		f34 = (str[i] == 34 && !f39) ? !f34 : f34;
		f39 = (str[i] == 39 && !f34) ? !f39 : f39;
		if (is_split(str[i], ';') == 1 && f34 == 0 && f39 == 0)
			i++;
		else if (!(j = 0))
		{
			while (str[i + j] && (is_split(str[i + j], ';') == 0
				|| (is_split(str[i + j], ';') == 1 && (f34 || f39))))
			{
				f39 = (str[i + ++j] == 39 && !f34) ? !f39 : f39;
				f34 = (str[i + j] == 34 && !f39) ? !f34 : f34;
			}
			if (!(split[word] = (char*)malloc(sizeof(char) * (j + 1))))
			{
				ft_free_split(split, word);
				return ;
			}
			ft_cytab(split[word++], str + i, 0, 0);
			i += j;
		}
	}
}
*/

char		**ft_split_mini(char const *s, char c)
{
	char	**bs;
	int		word;

	if (!s)
		return (NULL);
	word = ft_counter((char *)s, c);
	printf("word [%d]\n",word);
	if (!(bs = (char **)malloc(sizeof(char*) * (word + 1))))
		return (NULL);
	bs[word] = 0;
	ft_writing(bs, (char *)s, 0, 0);
	
	return (bs);
}

#include <stdio.h>

int			main(int ac, char **av)
{
	char	**tab;

//	tab = ft_split_mini("pwd;\"pw;d;pwd", ';');
	tab = ft_split_mini(av[1], ';');
	for (int i = 0; tab[i]; i++)
		printf("id[%d] ->  [%s]\n", i, tab[i]);
//	system("leaks a.out");
	(void)ac;
	(void)av;
	return (0);
}
