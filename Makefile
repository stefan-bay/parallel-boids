CXX = g++
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
TARGET = boids
SFML=
PARALLEL= -fopenmp -D USE_PARALLEL=1
## uncomment these to skip sfml compilation ##
# SFML=-D SKIPSFML=1
# LDFLAGS=

all: $(TARGET)

serial:
	$(CXX) $(SFML) main.cpp Vec2.cpp Boid.cpp -o $(TARGET)_serial $(LDFLAGS)

parallel:
	$(CXX) $(PARALLEL) $(SFML) main.cpp Vec2.cpp Boid.cpp -o $(TARGET)_parallel $(LDFLAGS)

$(TARGET): serial parallel

.PHONY: clean

clean:
	rm -f *.o *~ $(TARGET)_parallel $(TARGET)_serial
