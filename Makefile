CC = gcc
CFLAGS += -Wall -O3
DEPS = src/brain.h src/util.h

all: dirs bin/yabi
nofilter: all
nofilter: CFLAGS += -DBRAIN_NO_EOL_FILTER

dirs: bin obj src

bin:
	mkdir bin

obj:
	mkdir obj

src:
	mkdir src

obj/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/yabi: obj/main.o obj/brain.o obj/util.o
	$(CC) $(CFLAGS) $(LFLAGS) -o bin/yabi obj/main.o obj/brain.o obj/util.o -I.

clean:
	rm obj/brain.o obj/main.o obj/util.o bin/yabi
clean-all: clean
	rmdir bin
	rmdir obj
