CC = g++
CFLAGS = -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: main

main: main.o Map.o Entity.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp Map.hpp Entity.hpp
	$(CC) $(CFLAGS) $< -c

.PHONY: clean
clean:
	rm -f *.o main
