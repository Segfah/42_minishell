NAME	= libpf.a

PRINTF_F = ft_fprintf.c \
		   ft_vprintf.c \
		   flag_parsing.c \
		   text_format.c \
		   integer_format.c \
		   float_format.c \
		   conversions.c \
		   utils.c \
		   float_utils.c

SRCS	=  $(addprefix srcs/ft_printf/, $(PRINTF_F))

OBJS	= ${SRCS:.c=.o}

CC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror -I includes 

.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			ar rc ${NAME} ${OBJS}
			ranlib ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}


fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
