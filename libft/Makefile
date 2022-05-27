NAME =	libft.a

SRCS =	is/ft_isalpha.c is/ft_isdigit.c is/ft_isascii.c is/ft_isprint.c \
		is/ft_isalnum.c is/ft_isspace.c is/ft_isnumber.c

SRCS +=	str/ft_len.c str/ft_lcpy.c str/ft_lcat.c str/ft_chr.c \
		str/ft_rchr.c str/ft_ncmp.c str/ft_nstr.c str/ft_dup.c \
		str/ft_sub.c str/ft_join.c str/ft_trim.c str/ft_split.c  \
		str/ft_rev.c str/ft_mapi.c str/ft_iteri.c str/ft_join_with.c

SRCS +=	conv/ft_toupper.c conv/ft_tolower.c conv/ft_atoi.c conv/ft_itoa.c \
		conv/ft_itox.c conv/ft_utoa.c

SRCS +=	mem/ft_bzero.c mem/ft_memset.c mem/ft_memchr.c mem/ft_memcpy.c \
		mem/ft_memcmp.c mem/ft_memmove.c mem/ft_calloc.c mem/ft_free_split.c

SRCS += put/ft_putchar_fd.c put/ft_putnbr_fd.c put/ft_putendl_fd.c \
		put/ft_putstr_fd.c

SRCS += nbr/ft_nbrlen.c nbr/ft_croissant.c nbr/ft_decroissant.c nbr/ft_max.c \
		nbr/ft_min.c

SRCS +=	slist/ft_size.c slist/ft_new.c slist/ft_last.c \
		slist/ft_add_back.c slist/ft_add_front.c slist/ft_delone.c \
		slist/ft_clear.c slist/ft_iter.c slist/ft_map.c

SRCS +=	i_slist/ft_free.c i_slist/ft_first.c i_slist/ft_is_in.c

SRCS += dlist/ft_add.c dlist/ft_n.c dlist/ft_to_arr.c

OBJS		=	$(SRCS:.c=.o)

CC			=	gcc
AR			=	ar -rcs
RM			=	rm -rf

CFLAGS		=	-Wall -Wextra -Werror

$(VERBOSE).SILENT:

.c.o:
					${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all	:			$(NAME)

$(NAME):		$(OBJS)
				echo Making libft...
				${AR} ${NAME} ${OBJS}
				echo ✅

clean:
				echo Cleaning libft...
				${RM} ${OBJS}
				${RM} ${OBJS_BONUS}
				echo ✅

fclean:			clean
				${RM} ${NAME}

re:				fclean all

rebonus:		fclean bonus

.PHONY:			all bonus re rebonus clean fclean
