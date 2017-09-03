CC=g++-7
CFLAGS=-std=c++11 -Wall -Iinclude/
DEPS=include/LabyrinthLevel.hpp
OBJ=build/LabyrinthLevel.o build/test_lab_level.o
UNIT_TEST_OBJ=build/test_event.o
UNIT_TEST_CFLAGS=-std=c++11 -Wall -Iinclude/ -ggdb

build/%.o : src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

build/%.o : test/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

build/%.o : test/unit_tests/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(UNIT_TEST_CFLAGS)

bin/test_lab_level: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

bin/test_event: $(UNIT_TEST_OBJ)
	$(CC) -o $@ $^ $(UNIT_TEST_CFLAGS)
