/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 06:05:17 by corozco           #+#    #+#             */
/*   Updated: 2019/10/23 04:48:27 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;
	size_t len;

	len = ft_strlen(src);
	i = 0;
	if (len == 0)
		dst[i] = src[i];
	while (i < dstsize - 1 && i < len && dstsize != 0)
	{
		dst[i] = src[i];
		i++;
	}
	if (i > 0 && len > 0)
		dst[i] = 0;
	return (len);
}
