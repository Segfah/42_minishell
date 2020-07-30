/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 23:41:08 by corozco           #+#    #+#             */
/*   Updated: 2019/11/02 02:29:03 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	i;

	if (!s || !(str = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	i = 0;
	while (len-- && ft_strlen(s) > start)
		str[i++] = s[start++];
	str[i] = '\0';
	return (str);
}
