/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:01:15 by corozco           #+#    #+#             */
/*   Updated: 2020/08/04 20:49:15 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include "libft.h"

typedef struct	s_temp
{
	char		*env;
	char		**tabcmd;
	char		**strcmd;
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
void			clean_str(char *str);

/*
** gestion/pwd
*/
int				gestion_pwd(char **tabcmd, t_temp *tmp, int i);

/*
** gestion/cd
*/
void			gestion_cd(char *str);

/*
** gestion/env.c
*/
void			gestion_env(char **envp);

/*
** gestion/command_bin
*/
int				command_bin(char **tab);

/*
** gestion/encho
*/
void    		gestion_echo(char *str);

/*
** utils/ft_split_strcmd
*/
char			**ft_split_strcmd(char *s, char c);

#endif
