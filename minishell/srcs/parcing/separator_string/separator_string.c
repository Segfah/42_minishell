/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separator_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 13:58:31 by lryst             #+#    #+#             */
/*   Updated: 2020/10/15 17:59:25 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			separator_string(t_cmd **cmd, char *str, t_temp *tmp)
{
	int		i;
	int		echo;
	t_cmd	*new;

	echo = 0;
	i = 0;
	if (ft_strncmp(str, "echo ", 5) == 0 || ft_strncmp(str, "echo\0", 5) == 0)
		echo = 1;
	tmp->strcmd = ft_split_strcmd(str, echo);
	while (tmp->strcmd[i])
	{
		new = ft_lstnew_cmd(tmp->strcmd[i], tmp);
		ft_lstadd_back_cmd(cmd, new);
		i++;
	}
	remove_null_node(cmd);
	remove_space_node(cmd);
}
