/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prompt.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 02:15:36 by corozco           #+#    #+#             */
/*   Updated: 2020/07/31 02:34:44 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** elle sert à prendre le path à partir du dernier '/'
** Example 1:
** char *str = "/Users/&(USER)/Documents/42/42_minishell/minishell" , c = '/'
** le return ->     "/minishell"         (chaine malloc)
** Example 2: imaginant qu'on est dans la racine 'cd /'
** char *str = "/" c = '/'
** le return ->     "/"                  (chaine malloc)
*/

char			*ft_prompt(char *str)
{
	int			i;

	if (str)
	{
		i = ft_strlen(str);
		if (i == 1)
			if (str[0] == '/')
				return (ft_strdup("/"));
		while (0 <= i--)
			if (str[i] == '/')
				return (ft_strdup(&str[++i]));
	}
	return (NULL);
}
