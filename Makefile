CC = gcc
CFLAGS += -O3 -ansi -Wall
DEPS = brain.h

all: yabi

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

yabi: main.o brain.o
	$(CC) $(CFLAGS) -o yabi main.o brain.o -I.

clean:
	rm brain.o main.o yabi
