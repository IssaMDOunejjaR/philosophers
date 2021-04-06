# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/31 18:37:23 by iounejja          #+#    #+#              #
#    Updated: 2021/04/04 12:50:02 by iounejja         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc
FLAGS	= -Wall -Wextra -Werror
HEADERS	= -I headers/
LIB		= philo_one.a
EXEC	= philo_one
SRCS	= philo_one.c \
			srcs/utils.c \
			srcs/errors_check.c \
			srcs/create_philo.c
OBJS	= $(SRCS:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
		ar rcs $(LIB) $(OBJS)
		$(CC) $(FLAGS) $(HEADERS) $(LIB) -o $(EXEC)

%.o: %.c headers/*.h
	$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -rf *.o
	rm -rf $(LIB)
	rm -rf srcs/*o

fclean: clean
	rm -rf $(EXEC)

re: fclean all