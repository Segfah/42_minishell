/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 02:29:40 by corozco           #+#    #+#             */
/*   Updated: 2019/11/12 03:13:16 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	t_list	*new;
	t_list	*tmp;

	list = NULL;
	new = NULL;
	if (!lst || !f)
		return (NULL);
	list = lst;
	while (list->next)
	{
		tmp = ft_lstnew(f(list->content));
		if (tmp)
		{
			ft_lstadd_back(&new, tmp);
		}
		else
		{
			ft_lstclear(&lst, del);
			return (NULL);
		}
		list = list->next;
	}
	ft_lstadd_back(&new, ft_lstnew(f(list->content)));
	return (new);
}
