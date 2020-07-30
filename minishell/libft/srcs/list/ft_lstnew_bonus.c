/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 07:38:32 by corozco           #+#    #+#             */
/*   Updated: 2019/10/16 05:41:18 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*tmp;

	if (!(tmp = ft_memalloc(sizeof(t_list))))
		return (NULL);
	if (content)
		tmp->content = content;
	else
		tmp->content = NULL;
	tmp->next = NULL;
	return (tmp);
}
