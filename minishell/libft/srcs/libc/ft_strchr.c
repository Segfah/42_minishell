/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 04:45:55 by corozco           #+#    #+#             */
/*   Updated: 2019/10/23 04:55:32 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	int		k;
	char	tmp_c;

	k = ft_strlen(s);
	i = 0;
	tmp_c = (char)c;
	while (i <= k)
	{
		if (s[i] == tmp_c)
			return ((char*)s + i);
		i++;
	}
	return (NULL);
}
