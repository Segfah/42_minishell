# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lryst <lryst@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/20 13:43:17 by lryst             #+#    #+#              #
#    Updated: 2020/01/20 15:05:55 by lryst            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY : all clean fclean re up

CC = gcc $(INCLUDES) $(CFLAGS)

CFLAGS = -Wall -Wextra -Werror 

NAME = libpf.a

HEADERS = ft_fprintf.h

INCLUDES = -I 

SRCS =	ft_conv.c\
		ft_flags_m.c\
		ft_flags_z.c\
		ft_full_flags.c\
		ft_len.c\
		ft_parse.c\
		ft_precision.c\
		ft_print_char.c\
		ft_print_di.c\
		ft_print_s.c\
		ft_print_c.c\
		ft_print_maj_x.c\
		ft_print_p.c\
		ft_print_u.c\
		ft_print_x.c\
		ft_printf.c\
		ft_widths.c\
		ft_percent.c\
		ft_check_struct.c\
		ft_print_nbr.c\
		ft_s_wp.c\
		ft_s_lz_p.c\
		ft_s_w_p.c

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(SRCS) $(OBJS) $(HEADERS)
		@ar rc $(NAME) $(OBJS)
		@ranlib $(NAME)
		@echo "\033[032mlibprintf : Object files Created\033[0m"
		@echo "\033[032mlibprintf : $(NAME) Created\033[0m"

clean :
	@rm -f $(OBJS) $(LIST)
	@echo "\033[32mlibprintf : Object files Removed\033[0m"

fclean : clean
	@rm -f $(NAME) $(LIST)
	@echo "\033[32mlibprintf : $(NAME) Removed\033[0m"

up : all clean

re : fclean all

.SILENT: $(OBJS) 