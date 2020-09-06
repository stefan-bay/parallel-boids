#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>

#include "Vec2.h"
#include "Boid.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1600, 1000), "SFML works!");
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);
    vector<sf::CircleShape> shapes;
    for (int i = 0; i < 10; i++) {
      sf::CircleShape shape(10.f);
      shape.setPosition(800, 500);
      shapes.push_back(shape);
    }

    vector<Boid> boids;
    for (int i = 0; i < 10; i++) {
        Boid b(800, 500);
        boids.push_back(b);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // move
        for (int i = 0; i < shapes.size(); i++) {
          // sf::Vector2f pos = shapes[i].getPosition();
          // float x = pos.x + 1;
          // float y = pos.y;
          boids[i].update();
          shapes[i].setPosition(boids[i].position.x, boids[i].position.y);
        }


        for (int i = 0; i < shapes.size(); i++) {
          window.draw(shapes[i]);
        }

        // window.draw(shape);
        window.display();
    }

    return 0;
}
