/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 01:51:46 by corozco           #+#    #+#             */
/*   Updated: 2020/10/01 20:52:41 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		gestion_pwd(char **strcmd, t_temp *tmp)
{
	if (strcmd[1] && !is_redi(strcmd[1]))
	{
		ft_printf("pwd: too many arguments\n");
		return ;
	}
	tmp->env = getcwd(NULL, 0);
	ft_printf("%s\n", tmp->env);
	free(tmp->env);
	tmp->env = NULL;
}
