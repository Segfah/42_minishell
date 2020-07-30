/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <corozco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 01:53:15 by corozco           #+#    #+#             */
/*   Updated: 2019/10/20 20:15:42 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list *tmp;

	tmp = NULL;
	if (lst && f)
	{
		tmp = lst;
		while (tmp->next)
		{
			f(tmp->content);
			tmp = tmp->next;
		}
		f(tmp->content);
	}
}
