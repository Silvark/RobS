CC = g++
CFLAGS = -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

OBJ = Weapons.o Rob.o Entity.o Commands.o GUIElements.o Player.o GameLogic.o Map.o Game.o
HEAD = Weapons.hpp Rob.hpp Entity.hpp Commands.hpp GUIElements.hpp Player.hpp GameLogic.hpp Map.hpp Game.hpp

all: main clean

main: main.o $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp headers/$(HEAD)
	$(CC) $(CFLAGS) $< -c

.PHONY: clean
clean:
	rm -f *.o

purge: clean
	rm -f main
