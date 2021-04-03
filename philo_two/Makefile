# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iounejja <iounejja@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/03 14:23:54 by iounejja          #+#    #+#              #
#    Updated: 2021/04/03 14:43:53 by iounejja         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC		= gcc
FLAGS	= -Wall -Wextra -Werror
HEADERS	= -I headers/
LIB		= philo_two.a
EXEC	= philo_two
SRCS	= philo_two.c \
			srcs/utils.c \
			srcs/errors_check.c \
			srcs/create_philo.c
OBJS	= $(SRCS:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJS)
		ar rcs $(LIB) $(OBJS)
		$(CC) $(HEADERS) $(LIB) -o $(EXEC)

%.o: %.c headers/*.h
	$(CC) $(HEADERS) -c $< -o $@

clean:
	rm -rf *.o
	rm -rf $(LIB)
	rm -rf srcs/*o

fclean: clean
	rm -rf $(EXEC)

re: fclean all