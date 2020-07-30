/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 01:42:01 by corozco           #+#    #+#             */
/*   Updated: 2019/11/02 02:13:34 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	size_t			ol;
	unsigned char	*tmp_dst;
	unsigned char	*tmp_src;

	ol = 0;
	i = 0;
	tmp_dst = (unsigned char *)dst;
	tmp_src = (unsigned char *)src;
	while (i < len)
	{
		if (dst == src + i)
			ol = i;
		i++;
	}
	if (ol == 0)
		return (ft_memcpy(dst, src, len));
	i = 0;
	while (i < len)
	{
		*(tmp_dst + len - 1 - i) = *(tmp_src + len - 1 - i);
		i++;
	}
	return (dst);
}
