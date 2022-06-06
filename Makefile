SRC = main.c ./utils/*.c

#-fsanitize=thread

all:
	gcc $(SRC)

run: all
	./a.out 4 410 200 200