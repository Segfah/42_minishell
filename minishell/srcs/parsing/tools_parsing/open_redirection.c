/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 16:58:48 by corozco           #+#    #+#             */
/*   Updated: 2020/10/22 16:58:49 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_redi(char *str)
{
	return (!(ft_strcmp(">", str)) || !(ft_strcmp(">>", str))
		|| !(ft_strcmp("<", str)));
}

int		simple_redi(char *path, t_temp *tmp, int key)
{
	(tmp->fd > 0) ? close(tmp->fd) : 0;
	tmp->fd = 0;
	if ((tmp->fd = open(path, O_RDWR | O_TRUNC |
			O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
	{
		key ? ft_nb_exit(25) : 0;
		ft_printf("minishell: %s: %s\n", strerror(errno), path);
		return (-1);
	}
	return (0);
}

int		double_redi(char *path, t_temp *tmp, int key)
{
	(tmp->fd > 0) ? close(tmp->fd) : 0;
	tmp->fd = 0;
	if ((tmp->fd = open(path, O_APPEND | O_WRONLY | O_CREAT, 0644)) == -1)
	{
		key ? ft_nb_exit(25) : 0;
		ft_printf("minishell: %s: %s\n", strerror(errno), path);
		return (-1);
	}
	return (0);
}

int		contre_redi(char *path, t_temp *tmp, int key)
{
	(tmp->fdi > 0) ? close(tmp->fdi) : 0;
	tmp->fdi = 0;
	if ((tmp->fdi = open(path, O_RDONLY)) == -1)
	{
		key ? ft_nb_exit(25) : 0;
		ft_printf("minishell: %s: %s\n", strerror(errno), path);
		return (-1);
	}
	return (0);
}
