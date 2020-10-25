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
	if (tmp->flag[1] == 1)
	{
		tmp->oldfd = dup(1);
		dup2(tmp->fd, 1);
	}
	tmp->env = getcwd(NULL, 0);
	ft_printf("%s\n", tmp->env);
	ft_free(tmp->env);
	(tmp->flag[1] == 1) ? dup2(tmp->oldfd, 1) : 0;
	(void)strcmd;
}
