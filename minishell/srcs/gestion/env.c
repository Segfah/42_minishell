/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/05 23:02:07 by corozco           #+#    #+#             */
/*   Updated: 2020/08/06 02:09:55 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				gestion_env(t_lists *head)
{
	t_lists			*tmp;

	tmp = head;
	while (tmp != NULL)
	{
		ft_printf("%s=", tmp->name);
		ft_printf("%s\n", tmp->data);
		tmp = tmp->next;
	}
}
