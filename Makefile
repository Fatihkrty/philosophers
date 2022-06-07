NAME = philosophers
SRC = main.c ./utils/*.c

#-fsanitize=thread

all:
	gcc $(SRC) -lpthread -Wall -Werror -Wextra



run: all
	./a.out 11 610 200 200

# NAME = philo

# SRC = $(wildcard ./utils/*.c) main.c

# CC = gcc

# CFLAGS = -Wall -Wextra -Werror -lpthread

# OBJ = $(SRC:.c=.o)

# $(NAME): $(OBJ)
# 		$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

# all: $(NAME)

# clean:
# 		rm -rf $(OBJ)

# fclean:
# 		rm -rf $(OBJ) $(NAME)

# re: fclean all

# .PHONY: all re clean fclean