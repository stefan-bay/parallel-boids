# ifeq ($(shell uname), Darwin)
# SFMLPATH = ./SFML-2.5.1-macos-clang
# endif

CXX = g++
# INCLUDE = -I $(SFMLPATH)/include
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET = boids.out
SFML=
# uncomment this to skip sfml compilation
# SFML=-D SKIPSFML=1

all: $(TARGET)

main.o: main.cpp
	$(CXX) -c main.cpp $(SFML)

Vec2.o: Vec2.cpp
	$(CXX) -c Vec2.cpp

Boid.o:
	$(CXX) -c Boid.cpp

$(TARGET): main.o Vec2.o Boid.o
	$(CXX) main.o Vec2.o Boid.o -o $(TARGET) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f *.o *~ data.txt data.dat $(TARGET)
