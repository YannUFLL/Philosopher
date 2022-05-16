# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ydumaine <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/02 12:48:02 by ydumaine          #+#    #+#              #
#    Updated: 2022/05/16 19:09:45 by ydumaine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	srcs/main.c srcs/utils.c srcs/action.c srcs/forks.c srcs/init.c\
		srcs/utils2.c\

OBJS = ${SRCS:.c=.o}

NAME = philo

CC = cc

LINK = cc -o

RM = rm -f

HEADER = -I include/

CFLAGS = -Werror -Wextra -Wall -g
#-g -fsanitize=thread

.c.o: 
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o} ${HEADER}

${NAME}:	${OBJS}
			${LINK} ${NAME} ${OBJS} 
#-g -fsanitize=thread

all:		${NAME}

clean:
			${RM} ${OBJS} ${BOBJS}

fclean:     clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re bonus
