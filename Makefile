CFLAGS += -Wall -O3 -I include -I lib
LFLAGS += -Wall -O3
DEPS = lib/brain.h include/util.h
OBJECTS = obj/util.o
TARGET_OBJECTS = obj/main.o
TEST_OBJECTS = obj/tests.o

BINARY = bin/yabi
TEST_BINARY = bin/yatests

all: dirs yabin tests

yabin: $(BINARY)
tests: $(TEST_BINARY)

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

$(BINARY): $(OBJECTS) $(TARGET_OBJECTS)
	$(CC) $(LFLAGS) $^ -o $@

$(TEST_BINARY): $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $(LFLAGS) $^ -o $@

test: $(TEST_BINARY)
	./$(TEST_BINARY)

clean:
	rm $(OBJECTS) $(BINARY) $(TEST_BINARY)
clean-all: clean
	rmdir bin
	rmdir obj
