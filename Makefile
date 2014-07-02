CFLAGS += -O3 -ansi -Wall

all: yabi

yabi:
	gcc $(CFLAGS) -c brain.c main.c
	gcc $(CFLAGS) brain.o main.o -o yabi

clean:
	rm brain.o main.o yabi
