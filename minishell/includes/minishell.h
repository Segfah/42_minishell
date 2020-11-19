/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lryst <lryst@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:01:15 by corozco           #+#    #+#             */
/*   Updated: 2020/11/19 11:12:05 by lryst            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <signal.h>
# include <string.h>
# include <errno.h>
# include "libft.h"
# include <fcntl.h>
# include <sys/stat.h>

typedef struct		s_lists
{
	char			*name;
	char			*data;
	struct s_lists	*next;
}					t_lists;

typedef struct		s_fd
{
	int				fd;
	struct s_fd		*next;
}					t_fd;

/*
** flag[0] = cmd existe
** flag[1] = redi exite
** flag[2] = pipe existe
** tabpath = cmd bin
** status = pour tabpath
*/

typedef struct		s_temp
{
	char			*prompt;
	char			*env;
	char			**tabcmd;
	char			**strcmd;
	char			**strcmdin;
	t_lists			*varenv;
	t_lists			*exportenv;
	char			*tab[2];
	char			**tabpath;
	int				status;
	int				flag[4];
	int				fd;
	int				fdi;
	int				oldfd;
	char			*hnull;
	char			***inpipe;
	char			***outpipe;
}					t_temp;

typedef struct		s_cmd
{
	char			*input;
	char			*output;
	int				ret;
	struct s_cmd	*next;
}					t_cmd;

int					g_ret;

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
int					ft_getline(t_temp *tmp);

/*
**	parsing/tools/cmd_exit
*/
int					cmd_exist(char *cmd, t_temp *tmp);

/*
**	parsing/tools/redirection
*/
int					check_redi(char **cmd, t_temp *tmp, int key);
void				skip_redi(char **cmd, t_temp *tmp);

/*
** parsing/tools/open_rediction
*/
int					is_redi(char *str);
int					simple_redi(char *path, t_temp *tmp);
int					double_redi(char *path, t_temp *tmp);
int					contre_redi(char *path, t_temp *tmp);

/*
** parsing/tools/tab3d
*/
int					split3d(t_cmd *cmd, t_temp *tmp);
void				clean_tab2d(char **tabin, char **tabout);

/*
** ************************************************************************
** **************************gestion***************************************
** ************************************************************************
*/

/*
** gestion/cd
*/
void				gestion_cd(char **strcmd, t_temp *tmp, int key);

/*
** env.c
*/
int					save_env(t_lists **head, char **envp);
void				gestion_env(char **strcmd, t_temp *tmp, int key);
/*
** gestion/export
*/
void				gestion_export(t_temp *tmp, int i, int key);

/*
** gestion/pwd
*/
void				gestion_pwd(char **strcmd, t_temp *tmp);

/*
** gestion/unset
*/
void				gestion_unset(t_temp *tmp, int key);

/*
** **************************gestion/tools*********************************
*/
/*
** tools_env_export
*/
void				print_list(t_lists *head, int key);
int					lback(t_lists **alst, char *str, char *str2);
int					cpy_env(t_lists **cpy, t_lists *list);
int					change_list(t_lists *head, char *ss, char *newdata);

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
int					command_bin(char **tab, t_temp *tmp, int key);

void				gestion_nani(char **tab);

/*
** utils/ft_split_strcmd
*/
char				**ft_split_strcmd(char *s, int echo);

/*
** gestion/echo/echo
*/
char				*gestion_echo_option(char *str, char *arg);
void				gestion_echo(t_temp *tmp);

/*
** gestion/echo/ft_split_echo/count_word
*/
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
char				*remove_slash(char *str, int *i, char save);
char				*slash_sort(char *str, int *i, char *tab, t_lists *var);
char				*slash(char *str, int *i, char *tab, t_lists *var);

/*
** gestion/echo/single_cote
*/
char				*single_cote(char *str, char *tab);
char				*put_in_tab_single(char *str, int *i
						, char *tab, int j, t_lists *var);
char				*single_keep_cote(char *str, int *i
						, char *tab, t_lists *var);

/*
** gestion/echo/dcote
*/
char				*put_in_tab(char *str, int *i, char *tab
						, int j, t_lists *var);
char				*dcote(char *str, char *tab, t_lists *var);

/*
** gestion/echo/word
*/
char				*word(char *str, int *i, char *tab);

/*
** utils/free.c
*/
char				*ft_strcatdup(char *s1, char *s2);
void				ft_free_double_tab(char **tab);
void				ft_free_triple_tab(char ***tab3d);
void				free_cmd(t_cmd *cmd);
void				free_node_cmd(t_cmd *node);

/*
** gestion/controle
*/
void				controle(char *c);

/*
** main
*/
void				launcher(t_temp tmp);

int					ft_count_word(char *str);
char				*copy(char *s, int *end, int start);
char				*ft_fill_line(char *str, int *i, char *tab);
char				**ft_split_line(char *str);

void				separator_string(t_cmd **cmd, char *str, t_temp *tmp);

void				dcote_cmd(t_cmd *cmd, t_lists *var);
void				dcote_cmd_2(t_cmd *cmd, t_lists *revar, int size);
void				dcote_cmd_3(t_cmd *cmd, t_lists *revar, int *i, int *j);

void				check_node(t_cmd *cmd, t_temp *temp);

void				dcote_fill_slash(t_cmd *cmd, int *i, int *j);
void				dcote_count_slash(t_cmd *cmd, int *i, int *size);
void				dcote_fill_dollar(t_cmd *cmd, t_lists *revar,
						int *i, int *j);
void				dcote_count_dollar(t_cmd *cmd, t_lists *var,
						int *i, int *size);
void				before_count_dollar(t_cmd *cmd, t_lists *var,
						int *i, int *size);

void				ft_lstdelone_cmd(t_cmd *lst);
void				remove_space_node(t_cmd **cmd);
void				remove_null_node(t_cmd **cmd);

void				ft_lstadd_back_cmd(t_cmd **alst, t_cmd *new);
t_cmd				*ft_lstnew_cmd(char *input, t_temp *temp);
void				single_cote_cmd(t_cmd *cmd);
void				slash_cmd(t_cmd *cmd);

void				replace_isspace(t_cmd *cmd, int *i, int *j, char ascii);
void				dollar_cmd(t_cmd *cmd, t_lists *var);

void				count_slash(char *str, int *i);

int					message_error_pv(int pv);
int					multi_pv(char *str);
char				**tab_null(char **tab);

int					adeline2(char *s, char c, int n, int *i);
int					adeline(char *s, char cote, int n, int *i);
void				adeline_la_best(char *s, char cote, int *i);

void				ft_count_word_dollar(char *s, int *i, int *n);
char				*ft_fill_dollar(char *s, int *i, char *tab);

void				ft_count_word_slash_2(char *s, int *i, int *n);
void				ft_count_word_slash(char *s, int *i, int *n);
char				*ft_fill_slash(char *s, int*i, char *tab);
char				*ft_fill_slash_2(char *s, int *i, char *tab, int save);

void				ft_count_word_space(char *s, int *i, int *n, int *echo);

void				ft_count_word_char(char *s, int *i, int *n);
char				*ft_fill_char(char *s, int *i, char *tab);

char				*copy_adeline(char *s, int *i, char *tab);
char				*copy_adeline2(char *s, int *i, char *tab);
char				*copy(char *s, int *end, int start);

char				*copy(char *s, int *end, int start);
char				*copy_slash_m(char *s, int *i, char *tab, int save);
char				*copy_slash_p(char *s, int *i, char *tab, int save);
char				*copy_adeline2(char *s, int *i, char *tab);
char				*copy_adeline(char *s, int *i, char *tab);

int					cherche_echo(char **tab);
void				remove_all_space_node(t_cmd **cmd);
int					strcat_cmd(t_cmd **cmd);
void				printflist(t_cmd *cmd);
void				printftab(char **tab);
void				clean_tab2d_echo(char **tabin, char **tabout);
int					len_split3d(t_cmd *cmd);
int					print_error(int ret);
int					command_bin_2(char **tab_env, char **tab, t_temp *tmp, int key);
void				command_bin_3(t_temp *tmp);
void				free_export_tab(t_temp *tmp);

#endif
