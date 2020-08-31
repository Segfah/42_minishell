/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 07:38:32 by corozco           #+#    #+#             */
/*   Updated: 2020/08/29 23:31:55 by lryst            ###   ########.fr       */
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
