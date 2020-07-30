/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 08:17:40 by corozco           #+#    #+#             */
/*   Updated: 2019/11/02 02:24:06 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t j;
	size_t l;

	i = 0;
	j = 0;
	l = ft_strlen(needle);
	while (haystack[i] && i < len && j < l)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len && haystack[i + j])
			j++;
		i++;
	}
	if (l == 0)
		return ((char*)haystack);
	if (j == l)
		return ((char*)haystack + i - 1);
	return (NULL);
}
