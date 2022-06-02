SRC = main.c ./utils/*.c

all:
	gcc $(SRC) -lpthread

run: all
	./a.out 10 4100 2000 2000