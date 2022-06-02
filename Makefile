SRC = main.c ./utils/*.c

all:
	gcc $(SRC) -lpthread

run: all
	./a.out 10 400 200 200