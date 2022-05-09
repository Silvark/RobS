CC = g++
CFLAGS = -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: main

main: main.o Map.o entity.o weapon.o mine.o desertEagle.o bombe.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp Map.hpp entity.hpp weapon.hpp mine.hpp desertEagle.hpp bombe.hpp
	$(CC) $(CFLAGS) $< -c

.PHONY: clean
clean:
	rm -f *.o main
