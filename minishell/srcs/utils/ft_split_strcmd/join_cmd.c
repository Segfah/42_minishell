/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:13:49 by lryst             #+#    #+#             */
/*   Updated: 2020/10/20 11:27:24 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 
verifier quilny a pas despace dans les cases
tant quil y a pas despace */

/* char				*remove_cote(char *s)
{
	char *ret;
	int i;
	int j;
	
	i = 1;
	j = 0;
	if (!(ret = (char*)malloc(sizeof(char) * ft_strlen(s) - 1)))
		return (NULL);
	while (s[i + 1])
	{
		ret[j++] = s[i++];
	}
	ret[j] = '\0';
	return (ret);
}

char				**join_cmd(char **tab)
{
	char	**new;
	int		i;
	int 	n;
	int		j;

	i = 0;
	n = 0;
	j = -1;
	while (tab[i])
	{
		j = 0;
		if (tab[i][j]) == '\'' || tab[i][j] == '"')
			tab[i] = remove_cote(tab[i]);
		return (NULL);
	}
	return (new);
} */