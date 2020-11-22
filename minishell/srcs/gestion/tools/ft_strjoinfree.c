/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:22:59 by lryst             #+#    #+#             */
/*   Updated: 2020/11/22 19:34:26 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_strjoinfree(char *s1, char *s2)
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
