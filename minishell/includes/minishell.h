/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:01:15 by corozco           #+#    #+#             */
/*   Updated: 2020/08/02 22:27:53 by lryst            ###   ########.fr       */
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
	char		**cmdstr;
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

/*
** gestion/pwd
*/
int				gestion_pwd(char **tabcmd, t_temp *tmp, int i);

/*
** gestion/cd
*/
void			gestion_cd(char *str)

#endif
