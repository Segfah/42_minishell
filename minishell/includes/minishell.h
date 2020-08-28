/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:01:15 by corozco           #+#    #+#             */
/*   Updated: 2020/08/28 04:00:14 by corozco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include "libft.h"

typedef struct		s_lists
{
	char			*name;
	char			*data;
	struct s_lists	*next;
}					t_lists;

typedef struct		s_temp
{
	char			*prompt;
	char			*env;
	char			**tabcmd;
	char			**strcmd;
	t_lists			*varenv;
	t_lists			*exportenv;
	char			*tab[2];
}					t_temp;

void				general_free(t_temp *tmp);
/*
** drawings
*/
void				welcome(void);

/*
** prompt
*/
char				*ft_prompt(char *str);

/*
** Parsing
*/
void				ft_getline(t_temp *tmp);
void				clean_str(char *str);

/*
** ************************************************************************
** **************************gestion***************************************
** ************************************************************************
*/

/*
** gestion/cd
*/
void				gestion_cd(char *str);

/*
** env.c
*/
int					save_env(t_lists **head, char **envp);
void				gestion_env(t_temp *tmp);
/*
** gestion/export
*/
void				gestion_export(t_temp *tmp, int i);

/*
** gestion/pwd
*/
int					gestion_pwd(char **tabcmd, t_temp *tmp, int i);

/*
** gestion/unset
*/
void				gestion_unset(t_temp *tmp);

/*
** **************************gestion/tools*********************************
*/
/*
** tools_env_export
*/
void				print_list(t_lists *head, int key);
int					lback(t_lists **alst, char *str, char *str2);
int					cpy_env(t_lists **cpy, t_lists *list);

/*
** tools_env_unset
*/
int					check_env(char *str, int key);

/*
** tools_export
*/
void				range_export(t_lists *la);
int					search_env(char *str, t_temp *tmp, int key, char **data);

/*
** tools_list
*/
void				deletenode(t_lists *list, char *strkey);
void				free_node(t_lists *node);
void				free_list(t_lists *test);
/*
** ************************************************************************
*/

/*
** gestion/command_bin
*/
int					command_bin(char **tab, t_temp *tmp);

/*
** gestion/echo
*/
void    			gestion_echo(char *str, char *option, t_temp *temp);

/*
** utils/ft_split_strcmd
*/
char				**ft_split_strcmd(char *s, char c);

/*
** gestion/echo
*/
char				**ft_split_echo(char *s, t_temp *temp);
int					count_slash(char *str, int *j);
char				*double_cote(char *str, int *i, char *tab, t_temp *temp);
char				*single_cote(char *str, int *i, char *tab);
char				*dollar_variable(char *str, int *i, char *tab);

/*
** utils/free.c
*/
void    			ft_free(char *str);
void    			ft_free_double_tab(char **tab);

#endif
