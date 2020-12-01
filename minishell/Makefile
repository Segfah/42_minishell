# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lryst <lryst@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/24 05:41:03 by corozco           #+#    #+#              #
#    Updated: 2020/12/01 10:25:36 by lryst            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
#HEAD := -I./includes/ -I./libft/includes
HEAD := -I./includes/ -I./libft/includes -I./ft_fprintf

CFLAGS = -Wall -Wextra -Werror
CFLAGSF = -g3 -fsanitize=address -Wall -Wextra -Werror


SRC := \
	srcs/main.c \
	srcs/signal.c \
	srcs/drawings/welcome.c \
	srcs/prompt/ft_prompt.c \
	srcs/parsing/principal_parsing.c \
	srcs/gestion/pwd.c \
	srcs/gestion/cd.c \
	srcs/gestion/env.c \
	srcs/gestion/unset.c \
	srcs/gestion/command_bin.c \
	srcs/gestion/nani.c \
	srcs/gestion/exit.c \
	srcs/utils/ft_split_strcmd/ft_split_strcmd.c \
	srcs/utils/ft_split_strcmd/cmd_dollar.c \
	srcs/utils/ft_split_strcmd/cmd_slash.c \
	srcs/utils/ft_split_strcmd/space.c \
	srcs/utils/ft_split_strcmd/copy.c \
	srcs/utils/ft_split_strcmd/char.c \
	srcs/utils/initialize.c \
	srcs/gestion/tools/tools_env_export.c \
	srcs/gestion/tools/tools_env_unset.c \
	srcs/gestion/tools/tools_export.c \
	srcs/gestion/tools/tools_list.c \
	srcs/gestion/tools/tools_command_bin.c \
	srcs/gestion/tools/echo_option.c \
	srcs/gestion/tools/ft_strjoinfree.c \
	srcs/gestion/tools/ft_newstring.c \
	srcs/gestion/tools/dup_or_not.c \
	srcs/gestion/tools/is_var.c \
	srcs/gestion/export.c \
	srcs/utils/free.c \
	srcs/gestion/echo.c \
	srcs/utils/ft_split_line.c \
	srcs/parsing/separator_string/node_cmd.c \
	srcs/parsing/separator_string/delete_node.c \
	srcs/parsing/separator_string/separator_string.c \
	srcs/parsing/separator_string/dcote.c \
	srcs/parsing/separator_string/dcote_count.c \
	srcs/parsing/separator_string/dcote_fill.c \
	srcs/parsing/separator_string/single_cote.c \
	srcs/parsing/separator_string/slash.c \
	srcs/parsing/separator_string/dollar.c \
	srcs/utils/ft_strcatdup.c \
	srcs/utils/pv.c \
	srcs/utils/prints.c \
	srcs/parsing/tools_parsing/cmd_exist.c \
	srcs/parsing/tools_parsing/redirection.c \
	srcs/parsing/tools_parsing/open_redirection.c \
	srcs/parsing/tools_parsing/clean_espaces_echo.c \
	srcs/parsing/tools_parsing/error_line.c \
	srcs/parsing/tools_parsing/tab3d.c \
	srcs/parsing/tools_parsing/launcher_cmd.c \
	srcs/parsing/tools_parsing/clean_tab3d.c \
	srcs/parsing/tools_parsing/len_tab3d.c \
	srcs/parsing/tools_parsing/check_redi_flag.c \
	srcs/parsing/tools_parsing/check_redi_2.c \
	srcs/parsing/tools_parsing/llist_astring.c \
	srcs/parsing/tools_pipes/gpipes.c \
	srcs/parsing/tools_pipes/close_pipes.c \
	srcs/utils/adelines.c 

OBJS = $(addprefix objs/, $(SRC:.c=.o))
#color
COM_COLOR   = \033[0;34m
OBJ_COLOR   = \033[0;36m
OK_COLOR    = \033[0;32m
ERROR_COLOR = \033[0;31m
WARN_COLOR  = \033[0;33m
NO_COLOR    = \033[m

OK_STRING    = "[OK]"
ERROR_STRING = "[ERROR]"
WARN_STRING  = "[WARNING]"
COM_STRING   = "Compiling"

define run_and_test
printf "%b" "$(COM_COLOR)$(COM_STRING) $(OBJ_COLOR)$(@F)$(NO_COLOR)\r"; \
$(1) 2> $@.log; \
RESULT=$$?; \
if [ $$RESULT -ne 0 ]; then \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(ERROR_COLOR)$(ERROR_STRING)$(NO_COLOR)\n"   ; \
elif [ -s $@.log ]; then \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $@" "$(WARN_COLOR)$(WARN_STRING)$(NO_COLOR)\n"   ; \
else  \
  printf "%-60b%b" "$(COM_COLOR)$(COM_STRING)$(OBJ_COLOR) $(@F)" "$(OK_COLOR)$(OK_STRING)$(NO_COLOR)\n"   ; \
fi; \
cat $@.log; \
rm -f $@.log; \
exit $$RESULT
endef


all: $(NAME)
#@gcc $(CFLAGS) $(HEAD) $(OBJS) -o $(NAME) -L./libft -lft
$(NAME): $(OBJS)
	@make -sC ./libft
	@make -sC ./ft_fprintf
	@echo ''
	@gcc $(CFLAGS) $(HEAD) $(OBJS) -o $(NAME) -L./libft -lft -L./ft_fprintf -lpf
	@echo '	 '
	@echo '	......( \_/ ) '
	@echo '	......( o_o ) '
	@echo '	..../""""""""""""\======░ ▒▓▓█D' "$(WARN_COLOR)\t $(NAME)\t$(OK_COLOR)[CREATED]$(NO_COLOR)";
	@echo '	/"""""""""""""""""""\ '
	@echo '	\_@_@_@_@_@_@_@_@_@_/'

objs/%.o: %.c
	@mkdir -p $(dir $@)
	@$(call run_and_test,gcc $(CFLAGS) $(HEAD) -c $< -o $@)

clean:
	@rm -rf $(OBJS) objs
	@make clean -sC libft
	@make clean -sC ft_fprintf
	@printf "%b" "$(ERROR_COLOR)\tmake clean\t$(OK_COLOR)[SUCCESS]$(NO_COLOR)\n";
#	@make 42

fclean:
	@make fclean -sC libft
	@make fclean -sC ft_fprintf
	@rm -rf $(NAME) $(OBJS) objs
	@printf "%b" "$(ERROR_COLOR)\tmake fclean\t$(OK_COLOR)[SUCCESS]$(NO_COLOR)\n";

re: fclean all

#@gcc $(CFLAGS) $(HEAD) $(OBJS) -o $(NAME) -L./libft -lft
cn: $(OBJS)
	@make -sC ./libft
	@make -sC ./ft_fprintf
	@gcc $(CFLAGS) $(HEAD) $(OBJS) -o $(NAME) -L./libft -lft -L./ft_fprintf -lpf
	@echo 'simple ' "$(WARN_COLOR)\t $(NAME)\t$(OK_COLOR)[CREATED]$(NO_COLOR)";


#@gcc $(CFLAGSF) $(HEAD) $(OBJS) -o $(NAME) -L./libft -lft
cs: $(OBJS)
	@make -sC ./libft
	@make -sC ./ft_fprintf
	@gcc $(CFLAGSF) $(HEAD) $(OBJS) -o $(NAME) -L./libft -lft -L./ft_fprintf -lpf
	@echo 'sanitize' "$(WARN_COLOR)\t $(NAME)\t$(OK_COLOR)[CREATED]$(NO_COLOR)";

leaks:
	leaks $(NAME)

norme:
	@~/.norminette/norminette.rb libft/srcs libft/includes includes srcs/ ft_fprintf/*.c ft_fprintf/*.h

quimera:
	@echo '	 _**_**	'
	@echo '	_**___**	'
	@echo '	_**___**_________****	'
	@echo '	_**___**_______**___****	'
	@echo '	_**__**_______*___**___**	'
	@echo '	__**__*______*__**__***__**	'
	@echo '	___**__*____*__**_____**__*	'
	@echo '	____**_**__**_**________**	'
	@echo '	____**___**__**	'
	@echo '	___*___________*	'
	@echo '	__*_____________*	'
	@echo '	_*____0_____0____*	'
	@echo '	_*_______@_______*	'
	@echo '	_*_______________*	'
	@echo '	___*_____v_____*	'
	@echo '	_____**_____** 	Quimera '

#42:
#	@echo '		© 2020 42corozco'
#	@echo '		║▌█║▌│█│║▌║││█║▌║▌║'
