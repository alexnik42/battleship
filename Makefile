NAME 		= battleship

SRCS 		= $(wildcard srcs/*.c)

OBJS 		= ${SRCS:.c=.o}

HDRS 		= ./includes

CC 			= gcc

CFLAGS 		= -Wall -Wextra -Werror -I$(HDRS)

RM 			= rm -f

all: 		${NAME}

.c.o:		
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${OBJS}:	${HDRS}

${NAME}:	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean:
			${RM} ${OBJS}

fclean: 	clean
			${RM} ${NAME}

re: 		fclean all

.PHONY: 	all clean fclean re