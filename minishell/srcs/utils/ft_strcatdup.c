/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcatdup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 14:00:14 by lryst             #+#    #+#             */
/*   Updated: 2020/11/13 16:31:27 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				*ft_strcatdup(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	if (!(ret = (char*)malloc(sizeof(char) * (i + j) + 1)))
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		ret[i] = s1[i];
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i] = '\0';
	ft_free(s1);
	ft_free(s2);
	return (ret);
}
