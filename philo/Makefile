NAME	= philo

INCLUDES = -I$(HEADERS_DIRECTORY)

HEADERS_LIST = push_swap.h
HEADERS_DIRECTORY = ./includes/
HEADERS = $(addprefix $(HEADERS_DIRECTORY), $(HEADERS_LIST))

SRCS_DIRECTORY = ./src/
SRCS_LIST	= philo.c
SRCS = $(addprefix $(SRCS_DIRECTORY), $(SRCS_LIST))

OBJS_DIRECTORY = objects/
OBJS_LIST = $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS = $(addprefix $(OBJS_DIRECTORY), $(OBJS_LIST))

CC			= gcc

CFLAGS	= -Wall -Wextra -Werror

all:		${NAME}

$(NAME):	$(OBJS_DIRECTORY) $(OBJS)
			@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

$(OBJS_DIRECTORY):
			mkdir -p $(OBJS_DIRECTORY)

$(OBJS_DIRECTORY)%.o : $(SRCS_DIRECTORY)%.c $(HEADERS)
			@$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@
		
clean:
			@$(MAKE) -sC
			@rm -rf $(OBJS_DIRECTORY)

fclean:		clean
			@rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re bonus