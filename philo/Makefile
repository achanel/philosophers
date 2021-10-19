NAME		= philo

FILES		= philo.c utils.c

HEADER_FILE	= includes/philo.h

HEADER		= -I includes/

SDIR		= ./

SRCS		= $(patsubst %.c, ${SDIR}/%.c, $(FILES))

BONUS		= 

OBJS		= ${SRCS:.c=.o}

BONUS_OBJS	= ${BONUS:.c=.o}

CC			= gcc
RM			= rm -f

CFLAGS	= -Wall -Wextra -Werror

all:		${NAME}

.c.o:	
		 	${CC} $(HEADER) ${CFLAGS} -c $< -o $(<:.c=.o)

$(NAME):	${OBJS} ${HEADER_FILE}
				$(CC) $(HEADER) $(CFLAGS) $(OBJS) -o $(NAME)

# bonus:		${BONUS_OBJS} ${OBJS} 
# 					ar rcs ${NAME} $?
		
clean:
					${RM} ${OBJS} ${BONUS_OBJS}

fclean:		clean
					${RM} ${NAME}

re:					fclean all

.PHONY:		all clean fclean re bonus