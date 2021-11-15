NAME		= philo_bonus

FILES		= philo_bonus.c utils_bonus.c solve_bonus.c solve_utils_bonus.c

HEADER_FILE	= includes/philo_bonus.h

HEADER		= -I includes/

SDIR		= ./

SRCS		= $(patsubst %.c, ${SDIR}/%.c, $(FILES))

BONUS		= 

OBJS		= ${SRCS:.c=.o}

BONUS_OBJS	= ${BONUS:.c=.o}

CC			= gcc
RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

all:		${NAME}

.c.o:	
		 	${CC} ${CFLAGS} $(HEADER) -c $< -o $(<:.c=.o)

$(NAME):	${OBJS} ${HEADER_FILE}
				$(CC) $(CFLAGS) $(HEADER) $(OBJS) -o $(NAME)

clean:
					${RM} ${OBJS} ${BONUS_OBJS}

fclean:		clean
					${RM} ${NAME}

re:					fclean all

.PHONY:		all clean fclean re bonus