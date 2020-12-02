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
