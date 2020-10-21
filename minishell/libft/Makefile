# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: corozco <corozco@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/24 05:41:03 by corozco           #+#    #+#              #
#    Updated: 2020/08/30 03:46:49 by corozco          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
HEAD := -I includes/

CFLAGS = -Wall -Wextra -Werror

SRC := \
	srcs/libc/ft_memset.c \
	srcs/libc/ft_bzero.c \
	srcs/libc/ft_memcpy.c \
	srcs/libc/ft_memccpy.c \
	srcs/libc/ft_memmove.c \
	srcs/libc/ft_memchr.c \
	srcs/libc/ft_memcmp.c \
	srcs/libc/ft_strlen.c \
	srcs/libc/ft_strlen_no_space.c \
	srcs/libc/ft_isalpha.c \
	srcs/libc/ft_isdigit.c \
	srcs/libc/ft_isalnum.c \
	srcs/libc/ft_isascii.c \
	srcs/libc/ft_isprint.c \
	srcs/libc/ft_toupper.c \
	srcs/libc/ft_tolower.c \
	srcs/libc/ft_strchr.c \
	srcs/libc/ft_strrchr.c \
	srcs/libc/ft_lentab.c \
	srcs/libc/ft_strcmp.c \
	srcs/libc/ft_strncmp.c \
	srcs/libc/ft_strlcpy.c \
	srcs/libc/ft_strlcat.c \
	srcs/libc/ft_strnstr.c \
	srcs/libc/ft_atoi.c \
	srcs/libc/ft_calloc.c \
	srcs/libc/ft_strdup.c \
	srcs/libc/ft_substr.c \
	srcs/libc/ft_strjoin.c \
	srcs/libc/ft_strtrim.c \
	srcs/libc/ft_split.c \
	srcs/libc/ft_itoa.c \
	srcs/libc/ft_ltoa.c \
	srcs/libc/ft_gnl.c \
	srcs/libc/ft_itoa_base.c \
	srcs/libc/ft_strmapi.c \
	srcs/libc/ft_putchar.c \
	srcs/libc/ft_putchar_fd.c \
	srcs/libc/ft_putstr.c \
	srcs/libc/ft_putstr_fd.c \
	srcs/libc/ft_putendl_fd.c \
	srcs/libc/ft_putnbr_fd.c \
	srcs/libc/ft_memalloc.c \
	srcs/libc/ft_strncat.c \
	srcs/libc/ft_isupper.c \
	srcs/libc/ft_islower.c \
	srcs/libc/ft_free_split.c \
	srcs/libc/ft_free_tab.c \
	srcs/libc/ft_free.c \
	srcs/libc/ft_isspace.c

BNS := \
	srcs/list/ft_lstmap_bonus.c \
	srcs/list/ft_lstiter_bonus.c \
	srcs/list/ft_lstclear_bonus.c \
	srcs/list/ft_lstlast_bonus.c \
	srcs/list/ft_lstdelone_bonus.c \
	srcs/list/ft_lstsize_bonus.c \
	srcs/list/ft_lstadd_back_bonus.c \
	srcs/list/ft_lstadd_front_bonus.c \
	srcs/list/ft_lstnew_bonus.c \


SRCP := \
	srcs/printf/ft_printf.c \
	srcs/printf/ft_gestion_char.c \
	srcs/printf/ft_gestion_string.c \
	srcs/printf/ft_gestion_number.c \
	srcs/printf/ft_gestion_hexa.c \
	srcs/printf/ft_gestion_pointer.c \
	srcs/printf/ft_pf_check.c \
	srcs/printf/ft_pf_tools.c \

OBJS = $(addprefix objs/, $(SRC:.c=.o))
OBJB = $(addprefix objs/, $(BNS:.c=.o))
OBJP = $(addprefix objs/, $(SRCP:.c=.o))

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

$(NAME): $(OBJS) $(OBJB) $(OBJP)
	@ar rcs $(NAME) $(OBJS) $(OBJB) $(OBJP)

objs/%.o: %.c
	@mkdir -p $(dir $@)
	@$(call run_and_test,gcc $(CFLAGS) $(HEAD) -c $< -o $@)

clean:
	@rm -rf $(OBJS) $(OBJB) $(OBJP) objs

fclean:
	@rm -rf $(NAME) $(OBJS) $(OBJB) $(OBJP) objs

re: fclean all

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

42:
	@echo '		© 2020 42corozco'
	@echo '		║▌█║▌│█│║▌║││█║▌║▌║'
