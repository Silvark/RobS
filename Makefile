CC = g++
CFLAGS = -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

OBJ = Commands.o Entity.o Player.o Weapons.o GUIElements.o Map.o Game.o GameLogic.o
HEAD = Commands.hpp Entity.hpp Player.hpp Weapons.hpp GUIElements.hpp Map.hpp Game.hpp GameLogic.hpp

all: main clean

main: main.o $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp $(HEAD)
	$(CC) $(CFLAGS) $< -c

.PHONY: clean
clean:
	rm -f *.o

purge: clean
	rm -f main
