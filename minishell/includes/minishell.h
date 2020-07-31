/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: corozco <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:01:15 by corozco           #+#    #+#             */
/*   Updated: 2020/07/31 02:32:21 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include "libft.h"

typedef struct	s_temp
{
	char		*env;
	char		**tabcmd;
}				t_temp;

/*
** drawings
*/

void			welcome(void);

/*
** prompt
*/

char			*ft_prompt(char *str);

/*
** Parsing
*/

void			ft_getline(t_temp *tmp);

#endif
