NAME =	minishell
LIBFT = libft.a
SRCS = 	minishell.c lexer.c lexer_2.c lexer_3.c parser.c caller.c
SRCS +=	built-in.c env.c utils.c errors.c
OBJS = ${SRCS:.c=.o}


UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Linux)
	LIB = -lreadline -lhistory -L. -lft
endif
ifeq ($(UNAME_S), Darwin)
	READLINE_INC = -I ~/.brew/opt/readline/include
	LIB = -L ~/.brew/lib -lreadline -L ~/.brew/lib -lhistory -L. -lft
endif

all:	$(NAME)

$(VERBOSE).SILENT:

$(NAME):	$(LIBFT) $(OBJS)
		echo Making Minishell...
		gcc -g ${OBJS} ${LIB} -o ${NAME}
		echo ✅

$(LIBFT):
		${MAKE} -C ./libft
		cp ./libft/libft.a .


%.o:	%.c
		gcc -Werror -Wextra -Wall -g -c $< ${READLINE_INC}

clean:
		echo Cleaning objects...
		rm -rf ${OBJS}
		echo ✅

fclean:		clean
		${MAKE} -C ./libft fclean
		rm -rf libft.a
		echo Cleaning binary...
		rm -rf ${NAME}
		echo ✅

re:		fclean all

.PHONY: all clean fclean re
