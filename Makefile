NAME 		= battleship

SRCS 		= $(wildcard *.c)

OBJS 		= ${SRCS:.c=.o}

HDRS 		= b_header.h

CC 			= gcc

CFLAGS 		= -Wall -Wextra -Werror

RM 			= rm -f

all: 		${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

${OBJS}:	${HDRS}

clean:
			${RM} ${OBJS}
			${RM} ${TMPF}

fclean: 	clean
			${RM} ${NAME}

re: 		fclean all

.PHONY: 	all clean fclean re nf