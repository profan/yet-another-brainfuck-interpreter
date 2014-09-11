CC = gcc
CFLAGS += -Wall -O3
DEPS = src/brain.h src/util.h
OBJECTS = obj/brain.o obj/main.o obj/util.o

all: dirs yabin

YABI_BINARY = bin/yabi
yabin: $(YABI_BINARY)

nofilter: all
nofilter: CFLAGS += -DBRAIN_NO_EOL_FILTER

TEST_BINARY = yatests
testbin: bin/$(TEST_BINARY)

dirs: bin obj src

bin:
	mkdir bin

obj:
	mkdir obj

src:
	mkdir src

obj/%.o: src/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(YABI_BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(YABI_BINARY) $(OBJECTS) -I.

$(TEST_BINARY): $(OBJECTS)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(TEST_BINARY) $(OBJECTS) -I.

clean:
	rm $(OBJECTS) bin/$(YABI_BINARY) bin/$(TEST_BINARY)
clean-all: clean
	rmdir bin
	rmdir obj
