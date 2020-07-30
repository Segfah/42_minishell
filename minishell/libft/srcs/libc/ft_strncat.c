/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 07:56:04 by corozco           #+#    #+#             */
/*   Updated: 2019/11/02 02:24:43 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char *ptr;

	ptr = s1;
	while (*ptr)
		ptr++;
	while (n-- && *s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (s1);
}
