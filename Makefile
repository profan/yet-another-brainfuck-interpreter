CC = gcc
CFLAGS += -O3 -ansi -Wall
DEPS = src/brain.h

all: dirs bin/yabi

dirs: bin obj src

bin:
	mkdir bin

obj:
	mkdir obj

src:
	mkdir src

obj/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/yabi: obj/main.o obj/brain.o
	$(CC) $(CFLAGS) -o bin/yabi obj/main.o obj/brain.o -I.

clean:
	rm bin/brain.o bin/main.o bin/yabi
clean-all: clean
	rmdir bin
	rmdir obj
