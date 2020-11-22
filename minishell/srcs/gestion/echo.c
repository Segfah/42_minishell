/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 17:27:31 by lryst             #+#    #+#             */
/*   Updated: 2020/11/22 12:27:27 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_check_option_echo(char *s)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(s);
	if (s[i] == '-')
	{
		if (s[i + 1])
			i++;
		while (s[i] && s[i] == 'n')
			i++;
	}
	if (i == len)
		return (i);
	return (0);
}

void		dup_or_not(t_temp *tmp)
{
	if (tmp->flag[1] == 1)
	{
		tmp->oldfd = dup(1);
		dup2(tmp->fd, 1);
	}
}

char	*ft_newstring(size_t i)
{
	char	*str;
	size_t	zero;

	zero = 0;
	if (!(str = (char*)malloc(sizeof(char) * i + 1)))
		return (NULL);
	while (str && zero < i + 1)
	{
		str[zero] = '\0';
		zero++;
	}
	return (str);
}

char	*ft_strjoinfree(char *s1, char *s2)
{
	char	*tab;
	int		i;
	int		u;

	i = 0;
	u = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	tab = (char*)malloc(sizeof(char) * (ft_strlen((char *)s1) +
				ft_strlen((char *)s2)) + 1);
	if (tab == NULL)
		return (NULL);
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	while (s2[u])
		tab[i++] = s2[u++];
	tab[i] = '\0';
	free(s1);
	s1 = NULL;
	return (tab);
}

int			echo_cote_space(t_temp *tmp)
{
	int i;
	int count;
	char *str;

	i = 0;
	count = 0;
	if (tmp->strcmdin[1] && ((ft_check_option_echo(tmp->strcmd[1]) != 0) ||
	ft_strcmp(tmp->strcmdin[1]," ") == 0))
		return (1);
	str = ft_newstring(0);
	while (tmp->strcmdin[count] && (ft_strcmp(tmp->strcmdin[count]," ") != 0))
	{
		str = ft_strjoinfree(str, tmp->strcmd[count]);
		count++;
	}
	ft_printf("minishell: %s: command not found\n", str);
	ft_free(str);
	return (0);
}

void		gestion_echo_2(t_temp *tmp, int n, int i)
{
	while (tmp->strcmd[i])
	{
		ft_printf("%s", tmp->strcmd[i]);
		i++;
	}
	g_ret = 0;
	if (n == 0)
		ft_printf("\n");
}

void		gestion_echo(t_temp *tmp)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	dup_or_not(tmp);
	if (echo_cote_space(tmp) == 0)
		return ;
	if (tmp->strcmd[i + 1] != NULL)
		i++;
	else
		n = 1;
	if (tmp->strcmd[i + 1] != NULL)
		i++;
	
	if (ft_check_option_echo(tmp->strcmd[i]) != 0)
	{
		i++;
		if (tmp->strcmd[i + 1] != NULL)
			i++;
		n = 2;
	}
	gestion_echo_2(tmp, n, i);
	(tmp->flag[1] == 1) ? dup2(tmp->oldfd, 1) : 0;
}

int			check_echo_2(int *check, int *i, char c, char *s)
{
	if (s && s[*i] && (s[*i] == c || s[*i] == c - 40))
	{
		*check += 1;
		(*i)++;
		return (*check);
	}
	*check = 0;
	return (0);
}
