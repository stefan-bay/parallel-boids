#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>

#include "Vec2.h"
#include "Boid.h"

#include <iostream>
#include <fstream>

#include <string>

#define BOID_COUNT 100
#define WIDTH 1600
#define HEIGHT 1000

int main()
{
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Boids");
    // sf::CircleShape shape(100.f);
    // shape.setFillColor(sf::Color::Green);
    vector<sf::CircleShape> shapes;
    for (int i = 0; i < BOID_COUNT; i++) {
      sf::CircleShape shape(10.f);
      shape.setPosition(WIDTH/2, HEIGHT/2);
      shapes.push_back(shape);
    }

    vector<Boid> boids;
    for (int i = 0; i < BOID_COUNT; i++) {
        Boid b(WIDTH/2, HEIGHT/2);
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
        // ofstream datafile;
        // datafile.open ("data.txt");

        ofstream out;
        out.open("data.txt");
        for (int i = 0; i < shapes.size(); i++) {
          // sf::Vector2f pos = shapes[i].getPosition();
          // float x = pos.x + 1;
          // float y = pos.y;
          boids[i].update();
          shapes[i].setPosition(boids[i].position.x, boids[i].position.y);

          // cout << "--------" << i << "--------" << endl;
          boids[i].output(out);
          // datafile << boids[i].position.x << " " << boids[i].position.y << endl;
          // datafile << boids[i].acceleration.x << " " << boids[i].acceleration.y << endl;
          // datafile << boids[i].velocity.x << " " << boids[i].velocity.y << endl;
          // datafile ;
          // datafile << boids[i].velocity << endl;


        }
        // datafile.close();
        out.close();


        for (int i = 0; i < shapes.size(); i++) {
          window.draw(shapes[i]);
        }

        // window.draw(shape);
        window.display();
    }

    return 0;
}
