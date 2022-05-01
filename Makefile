CPP=g++
LD=g++



CPPFLAGS=-std=c++14
LDFLAGS=-std=c++14
LIBS=-lsfml-graphics -lsfml-window -lsfml-system -lsfml-network -lsfml-audio


all: robs

robs: testBen.o bombe.o maping.o
	$(LD) $(LDFLAGS)  testBen.o maping.o bombe.o -o robs $(LIBS)


testBen.o: testBen.cpp bombe.hpp maping.hpp
	$(CPP) $(CPPFLAGS) -c testBen.cpp $(LIBS)

maping.o: maping.cpp maping.hpp
	$(CPP) $(CPPFLAGS) -c maping.cpp $(LIBS)

bombe.o: bombe.cpp bombe.hpp maping.hpp
	$(CPP) $(CPPFLAGS) -c bombe.cpp $(LIBS)



clean:
	rm -f *.o robs
