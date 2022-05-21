CC = g++
CFLAGS = -Wall
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: main

main: main.o Map.o entity.o weapon.o mine.o desertEagle.o bombe.o joueur.o fonctionUtiles.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

<<<<<<< HEAD
%.o: %.cpp Map.hpp entity.hpp weapon.hpp mine.hpp desertEagle.hpp bombe.hpp joueur.hpp fonctionUtiles.hpp
=======
mainmenu: mainMenu.o Button.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp Map.hpp entity.hpp weapon.hpp mine.hpp desertEagle.hpp bombe.hpp Button.hpp GUIElement.hpp Commands.hpp
>>>>>>> c605a79032912249d80fabf01b3bd79c6eed368a
	$(CC) $(CFLAGS) $< -c

.PHONY: clean
clean:
	rm -f *.o main
