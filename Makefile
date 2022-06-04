SRC = main.c ./utils/*.c

#-fsanitize=thread

all:
	gcc $(SRC) -lpthread

run: all
	./a.out 10 410 200 200