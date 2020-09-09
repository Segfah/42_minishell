/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:01:15 by corozco           #+#    #+#             */
/*   Updated: 2020/09/09 20:29:22 by lryst            ###   ########.fr       */
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

typedef struct		s_cmd
{
	char			*input;
	char			*output;
	int				ret;
	struct	s_cmd	*next;
}					l_cmd;

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
** utils/ft_split_strcmd
*/
char				**ft_split_strcmd(char *s, int echo);

/*
** gestion/echo/echo
*/
char				*gestion_echo_option(char *str, char *arg);
void    			gestion_echo(l_cmd *cmd);

/*
** gestion/echo/ft_split_echo/count_word
*/
char				*remove_cote(char *s, int *start, char cote);
char				**ft_split_echo(char *s, int *i, t_temp *temp);
/*
** gestion/echo/ft_split_echo/count_word
*/

/*
** gestion/echo/dollar
*/
char				*put_dollar_variable(char *str, char *tab);
char				*check_dollar(char *str, int *i, t_lists *var);
int					count_dollar_varriable(char *str, int *j, t_lists *var);
int					is_it_var(char *str, t_lists *var);

/*
** gestion/echo/slash
*/
int					count_slash(char *str, int *j);
char				*remove_slash(char *str, int *i, char save);
char				*slash_sort(char *str, int *i, char *tab, t_lists *var);
char				*slash(char *str, int *i, char *tab, t_lists *var);

/*
** gestion/echo/single_cote
*/
char				*single_cote(char *str, char *tab);
char				*put_in_tab_single(char *str, int *i, char *tab, int j, t_lists *var);
char				*single_keep_cote(char *str, int *i, char *tab, t_lists *var);

/*
** gestion/echo/double_cote
*/
char				*put_in_tab(char *str, int *i, char *tab, int j, t_lists *var);
char				*double_cote(char *str, char *tab, t_lists *var);

/*
** gestion/echo/word
*/
char				*word(char *str, int *i, char *tab);

/*
** utils/free.c
*/
char				*ft_strcatdup(char *s1, char *s2);
void    			ft_free(char *str);
void    			ft_free_double_tab(char **tab);

/*
** gestion/controle
*/
void    			controle(char *c);

/*
** main
*/
int					launcher(t_temp tmp);

#endif
