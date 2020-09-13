# ifeq ($(shell uname), Darwin)
# SFMLPATH = ./SFML-2.5.1-macos-clang
# endif

CXX = g++
# INCLUDE = -I $(SFMLPATH)/include
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET = boids.out
SFML=
CPFLAGS=
# uncomment these to skip sfml compilation
SFML=-D SKIPSFML=1
LDFLAGS=
# uncomment for parallel version
# CPFLAGS=-fopenmp

all: $(TARGET)

main.o: main.cpp
	$(CXX) -c main.cpp $(CPFLAGS) $(SFML)

Vec2.o: Vec2.cpp
	$(CXX) -c Vec2.cpp $(CPFLAGS)

Boid.o:
	$(CXX) -c Boid.cpp $(CPFLAGS)

$(TARGET): main.o Vec2.o Boid.o
	$(CXX) $(CPFLAGS) main.o Vec2.o Boid.o -o $(TARGET) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ data.txt data.dat $(TARGET)
