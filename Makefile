# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 12:48:02 by ydumaine          #+#    #+#              #
#    Updated: 2022/05/02 16:33:28 by ydumaine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/main.c srcs/utils.c

OBJS = ${SRCS:.c=.o}

NAME = philosophers

CC = cc

LINK = cc -o

RM = rm -f

HEADER = -I include/

CFLAGS = -Werror -Wextra -Wall -g 

.c.o: 
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -D_REENTRANT ${HEADER}

${NAME}:	${OBJS}
			${LINK} ${NAME} ${OBJS} 

all:		${NAME}

clean:
			${RM} ${OBJS} ${BOBJS}

fclean:     clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
