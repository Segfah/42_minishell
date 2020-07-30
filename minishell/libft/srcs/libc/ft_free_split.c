/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 23:48:33 by corozco           #+#    #+#             */
/*   Updated: 2019/11/02 02:29:27 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_free_split(char **split, int i)
{
	while (i)
	{
		free(split[i]);
		i--;
	}
	free(split);
	split = NULL;
}
