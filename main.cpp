#include <iostream>
using namespace std;

// set "SFML" in makefile to skip compilation of SFML
#ifndef SKIPSFML
#include <SFML/Graphics.hpp>
#endif

#include "Vec2.h"
#include "Boid.h"
#include "defaults.h"


#include <fstream>
#include <csignal>

#include <stdio.h>
#include <vector>

#include <string>
#include <sstream>


void simulate_boids(string file, float count);
#ifndef SKIPSFML
void display_boids(string file, float count);
#endif

sig_atomic_t should_exit = 0;

// allows us to manually control the exit
void exithandler(int i) {
    cout << endl << "Exiting..." << endl;
    should_exit = 1;
}

int main(int argc, char *argv[])
{
    // overide ctrl-c
    signal(SIGINT, exithandler);

    if (argc < 3) {
        cout << "usage: " << argv[0] << " [simulate | display] file (boid_count)" << endl;
        cout << "default boid_count= 100" << endl;
        exit(1);
    }
    string command = string(argv[1]);
    string file = string(argv[2]);
    string scount;
    int b_count = BOID_COUNT;
    if (argc > 3) {
        try {
            scount = string(argv[3]);
            b_count = stoi(scount);
            if (b_count < 1)
                throw range_error("NO");
        } catch (exception const &e) {
            cout << "error: invalid integer " << scount << endl;
            exit(1);
        }
    }

    bool simulate = false;
    bool display = false;

    if (command == "simulate") {
        cout << "simulating " << b_count << " boids..." << endl;
        simulate = true;
    } else if (command == "display") {
        #ifdef SKIPSFML
        cout << "SFML is not compiled... exiting" << endl;
        exit(1);
        #endif

        cout << "displaying " << "boids..." << endl;
        display = true;
    } else {
        cout << "error: unrecognized command " << command << endl;
        exit(1);
    }

    if (simulate) {
        simulate_boids(file, b_count);
    } else if (display) {
        #ifndef SKIPSFML
        display_boids(file, b_count);
        #endif
    }

    return 0;
}

void simulate_boids(string file, float count) {
    FILE *out = fopen(file.c_str(), "a");

    vector<Boid> boids;
    // initialize boids
    for (int i = 0; i < count; i++) {
        Boid b(rand()%WIDTH, rand()%HEIGHT);
        // Boid b(WIDTH/2, HEIGHT/2);
        boids.push_back(b);
    }

    while (true) {
        if (should_exit) {
            fclose(out);
            exit(0);
        }

        // output their positions
        for (int i = 0; i < boids.size(); i++) {
            // boids[i].output(out);
            float values[] = {boids[i].position.x, boids[i].position.y, boids[i].velocity.x, boids[i].velocity.y};
            fwrite(&values, sizeof(float), 4, out);
        }

        // move boids TODO: PARALLELIZE
        for (int i = 0; i < boids.size(); i++) {
            boids[i].update(boids);
        }
    }
    fclose(out);
}

#ifndef SKIPSFML
void display_boids(string file, float count) {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Boids");

    vector<sf::CircleShape> shapes;
    for (int i = 0; i < count; i++) {
      sf::CircleShape shape(5.f);
      shape.setPosition(WIDTH/2, HEIGHT/2);
      shapes.push_back(shape);
    }

    FILE *in = fopen(file.c_str(), "r");
    fseek(in, 0, SEEK_END);
    size_t filesize = ftell(in);
    fseek(in, 0, SEEK_SET);

    while (window.isOpen() && ftell(in) <= (filesize - count))
    {
        if (should_exit) {
            fclose(in);
            window.close();
            exit(0);
        }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                fclose(in);
                window.close();
                exit(0);
            }
        }

        window.clear();


        // store all of boid values for this frame
        float *values = (float *)malloc(sizeof(float) * 4 * count);
        fread(values, sizeof(float), 4 * count, in);
        fseek(in, sizeof(float) * 4 * count, SEEK_CUR);

        // update and draw the shapes
        for (int i = 0; i < count; i++) {
            // update positions
            shapes[i].setPosition(values[(4 * i) + 0], values[(4 * i) + 1]);

            // draw shapes
            window.draw(shapes[i]);
        }

        window.display();
        // capture time when doing processing
        // subtract how much time the computation took by time between frames.
        // sleep remaining time
        // -- how long it took to draw per frame --
        sf::sleep(sf::milliseconds(10));
    }

    cout << "Exiting..." << endl;
    fclose(in);
    window.close();
    exit(0);


    return;
}
#endif
