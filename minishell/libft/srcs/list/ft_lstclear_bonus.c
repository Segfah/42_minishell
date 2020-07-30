/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 07:14:25 by corozco           #+#    #+#             */
/*   Updated: 2019/10/20 20:24:09 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *list;
	t_list *tmp;

	if (lst && del && *lst)
	{
		list = *lst;
		tmp = NULL;
		while (list->next)
		{
			tmp = list;
			list = list->next;
			ft_lstdelone(tmp, del);
		}
		ft_lstdelone(list, del);
		*lst = NULL;
	}
}
