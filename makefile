CC=g++-7
CFLAGS=-std=c++11 -Wall -Iinclude/
DEPS=include/LabyrinthLevel.hpp
OBJ=build/LabyrinthLevel.o build/test_lab_level.o

build/%.o : src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

build/%.o : test/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bin/test_lab_level: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

