CPP=g++
LD=g++



CPPFLAGS=-std=c++14
LDFLAGS=-std=c++14
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio


all: robs

robs: testBen.o bombe.o maping.o desertEagle.o fonctionUtiles.o weapon.o mine.o
	$(LD) $(LDFLAGS)  testBen.o maping.o bombe.o desertEagle.o fonctionUtiles.o weapon.o mine.o -o robs $(LIBS)

testBen.o: testBen.cpp bombe.hpp maping.hpp weapon.hpp
	$(CPP) $(CPPFLAGS) -c testBen.cpp $(LIBS)

weapon.o: weapon.cpp weapon.hpp
	$(CPP) $(CPPFLAGS) -c weapon.cpp $(LIBS)

fonctionUtiles.o: fonctionUtiles.cpp fonctionUtiles.hpp
	$(CPP) $(CPPFLAGS) -c fonctionUtiles.cpp $(LIBS)

maping.o: maping.cpp maping.hpp
	$(CPP) $(CPPFLAGS) -c maping.cpp $(LIBS)

bombe.o: bombe.cpp bombe.hpp maping.hpp weapon.hpp
	$(CPP) $(CPPFLAGS) -c bombe.cpp $(LIBS)

desertEagle.o: desertEagle.cpp desertEagle.hpp maping.hpp weapon.hpp
		$(CPP) $(CPPFLAGS) -c desertEagle.cpp $(LIBS)

mine.o: mine.cpp mine.hpp maping.hpp weapon.hpp
		$(CPP) $(CPPFLAGS) -c mine.cpp $(LIBS)


clean:
	rm -f *.o robs
