# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 12:48:02 by ydumaine          #+#    #+#              #
#    Updated: 2022/05/06 15:40:58 by ydumaine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = srcs/main.c srcs/utils.c srcs/action.c srcs/forks.c srcs/init.c 

OBJS = ${SRCS:.c=.o}

NAME = philo

CC = cc

LINK = cc -o

RM = rm -f

HEADER = -I include/

CFLAGS = -Werror -Wextra -Wall -g

.c.o: 
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} ${HEADER}

${NAME}:	${OBJS}
			${LINK} ${NAME} ${OBJS} 

all:		${NAME}

clean:
			${RM} ${OBJS} ${BOBJS}

fclean:     clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
