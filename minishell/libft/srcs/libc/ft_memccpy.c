/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:40:26 by corozco           #+#    #+#             */
/*   Updated: 2019/11/02 02:13:57 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			i;
	unsigned char	*ddst;
	unsigned char	*ssrc;
	unsigned char	cc;

	ddst = (unsigned char *)dst;
	ssrc = (unsigned char *)src;
	cc = (unsigned char)c;
	i = 0;
	while (i < n)
	{
		*(ddst + i) = *(ssrc + i);
		if (*(ssrc + i) == cc)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
