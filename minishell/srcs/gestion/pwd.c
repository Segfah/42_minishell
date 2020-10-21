/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 01:51:46 by corozco           #+#    #+#             */
/*   Updated: 2020/10/21 19:26:07 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		gestion_pwd(char **strcmd, t_temp *tmp)
{
	if (strcmd[1])
	{
		ft_printf("pwd: too many arguments\n");
		if (tmp->flag[1])
			close(tmp->fd);
		return ;
	}
	if (tmp->flag[1] == 1)
	{
		tmp->oldfd = dup(1);
		dup2(tmp->fd, 1);
	}
	tmp->env = getcwd(NULL, 0);
	ft_printf("%s\n", tmp->env);
	free(tmp->env);
	tmp->env = NULL;
	(tmp->flag[1] == 1) ? dup2(tmp->oldfd, 1) : 0;
}
