# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lryst <lryst@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/24 05:41:03 by corozco           #+#    #+#              #
#    Updated: 2020/08/06 02:33:02 by corozco          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = the_big_minishell
HEAD := -I./includes/ -I./libft/includes

CFLAGS = -Wall -Wextra -Werror
CFLAGSF = -g3 -fsanitize=address -Wall -Wextra -Werror


SRC := \
	srcs/main.c \
	srcs/drawings/welcome.c \
	srcs/prompt/ft_prompt.c \
	srcs/parcing/principal_parcing.c \
	srcs/parcing/clean_str.c \
	srcs/gestion/pwd.c \
	srcs/gestion/cd.c \
	srcs/gestion/env.c \
	srcs/gestion/command_bin.c \
	srcs/gestion/echo.c \
	srcs/utils/ft_split_strcmd.c \
	srcs/utils/ft_split_echo.c \
	srcs/gestion/tools/tools_env_export.c \
	srcs/gestion/export.c


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

$(NAME): $(OBJS)
	@make -sC ./libft
	@echo ''
	@gcc $(CFLAGS) $(HEAD) $(OBJS) -o $(NAME) -L./libft -lft
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
	@printf "%b" "$(ERROR_COLOR)\tmake clean\t$(OK_COLOR)[SUCCESS]$(NO_COLOR)\n";
#	@make 42

fclean:
	@make fclean -sC libft
	@rm -rf $(NAME) $(OBJS) objs
	@printf "%b" "$(ERROR_COLOR)\tmake fclean\t$(OK_COLOR)[SUCCESS]$(NO_COLOR)\n";

re: fclean all

cn: $(OBJS)
	@make -sC ./libft
	@gcc $(CFLAGS) $(HEAD) $(OBJS) -o $(NAME) -L./libft -lft
	@echo 'simple ' "$(WARN_COLOR)\t $(NAME)\t$(OK_COLOR)[CREATED]$(NO_COLOR)";

cs: $(OBJS)
	@make -sC ./libft
	@gcc $(CFLAGSF) $(HEAD) $(OBJS) -o $(NAME) -L./libft -lft
	@echo 'sanitize' "$(WARN_COLOR)\t $(NAME)\t$(OK_COLOR)[CREATED]$(NO_COLOR)";

leaks:
	leaks minishell

normi:
	norminette includes
	norminette srcs

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
