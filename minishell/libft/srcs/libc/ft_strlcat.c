/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 07:51:11 by corozco           #+#    #+#             */
/*   Updated: 2019/10/23 04:49:48 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t src_len;
	size_t dest_len;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dstsize <= dest_len)
		return (src_len + dstsize);
	if (src_len < (dstsize - dest_len))
		ft_strncat(dst, src, src_len + 1);
	else
	{
		ft_strncat(dst, src, dstsize - dest_len - 1);
		dst[dstsize - 1] = '\0';
	}
	return (dest_len + src_len);
}
