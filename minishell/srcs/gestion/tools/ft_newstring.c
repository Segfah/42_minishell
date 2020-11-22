/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newstring.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:25:51 by lryst             #+#    #+#             */
/*   Updated: 2020/11/22 19:33:13 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_newstring(size_t i)
{
	char	*str;
	size_t	zero;

	zero = 0;
	if (!(str = (char*)malloc(sizeof(char) * i + 1)))
		return (NULL);
	while (str && zero < i + 1)
	{
		str[zero] = '\0';
		zero++;
	}
	return (str);
}
