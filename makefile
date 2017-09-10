CC=g++-7
CFLAGS=-std=c++14 -Wall -Iinclude/
DEPS=include/LabyrinthLevel.hpp include/Event.hpp include/EventFwd.hpp
OBJ=build/LabyrinthLevel.o build/Event.o
UNIT_TEST_OBJ=build/test_event.o
UNIT_TEST_CFLAGS=-std=c++14 -Wall -Iinclude/ -ggdb

build/%.o : src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

build/%.o : test/unit_tests/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(UNIT_TEST_CFLAGS)

bin/test_event: $(UNIT_TEST_OBJ) $(OBJ)
	$(CC) -o $@ $^ $(UNIT_TEST_CFLAGS)
