/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:01:15 by corozco           #+#    #+#             */
/*   Updated: 2020/11/26 00:59:28 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPES_H
# define PIPES_H

typedef struct		s_fdpipes
{
	int				*fd;
	int				k;
	int				s;
}					t_fdpipes;

void				gpipes(t_temp *tmp, t_cmd *cmd, int j);
void				close_gpipes(t_temp *tmp, int *fd);

#endif
