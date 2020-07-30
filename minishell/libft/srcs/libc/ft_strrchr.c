/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 05:15:04 by corozco           #+#    #+#             */
/*   Updated: 2019/11/02 02:22:49 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		k;
	char	*tmp;
	char	tmp_c;

	k = ft_strlen(s);
	tmp = NULL;
	i = 0;
	tmp_c = (char)c;
	while (i <= k)
	{
		if (s[i] == tmp_c)
			tmp = (char*)&s[i];
		i++;
	}
	return (tmp);
}
