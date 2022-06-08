# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fkaratay <fkaratay@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/08 16:20:10 by fkaratay          #+#    #+#              #
#    Updated: 2022/06/08 17:03:16 by fkaratay         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = $(wildcard ./src/*.c) main.c

CC = gcc

CFLAGS = -Wall -Wextra -Werror -lpthread

OBJ = $(SRC:.c=.o)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

all: $(NAME)

clean:
		rm -rf $(OBJ)

fclean:
		rm -rf $(OBJ) $(NAME)

re: fclean all

.PHONY: all re clean fclean
