CC = g++
CFLAGS = -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

OBJ = main.o Map.o entity.o weapon.o mine.o desertEagle.o bombe.o joueur.o fonctionUtiles.o Game.o
HEAD = Map.hpp entity.hpp weapon.hpp mine.hpp desertEagle.hpp bombe.hpp Button.hpp GUIElement.hpp Commands.hpp joueur.hpp fonctionUtiles.hpp Game.hpp
all: main

main: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

mainmenu: mainMenu.o Button.o Commands.o Game.o Map.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp $(HEAD)
	$(CC) $(CFLAGS) $< -c

.PHONY: clean
clean:
	rm -f *.o main mainmenu
