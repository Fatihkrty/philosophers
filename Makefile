SRC = main.c ./utils/*.c

all:
	gcc $(SRC) -lpthread

run: all
	./a.out 50 410 200 200