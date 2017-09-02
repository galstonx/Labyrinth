CC=g++
CFLAGS=-std=c++11 -Wall
DEPS=LabyrinthLevel.hpp
OBJ=LabyrinthLevel.o test_lab_level.o

%.o : %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

test_lab_level: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

