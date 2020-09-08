#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>

#include "Vec2.h"
#include "Boid.h"

#include <fstream>
#include <csignal>

#include <string>
#include <sstream>

#define BOID_COUNT 100
#define WIDTH 1600
#define HEIGHT 1000

void simulate_boids(float count);
void display_boids(float count);

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

    if (argc < 2) {
        cout << "usage: " << argv[0] << " [simulate | display] boid_count" << endl;
        exit(1);
    }
    string command = string(argv[1]);
    string scount;
    int b_count = BOID_COUNT;
    if (argc > 2) {
        try {
            scount = string(argv[2]);
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
        cout << "displaying " << "boids..." << endl;
        display = true;
    } else {
        cout << "error: unrecognized command " << command << endl;
        exit(1);
    }

    if (simulate) {
        simulate_boids(b_count);
    } else if (display) {
        display_boids(b_count);
    }

    return 0;
}

void simulate_boids(float count) {
    // TODO: file output
    // boids[i].output(out);
    //outfile.open("test.txt", std::ios_base::app);
    ofstream out;
    out.open("data.txt", ios_base::app);

    vector<Boid> boids;
    // initialize boids
    for (int i = 0; i < count; i++) {
        Boid b(WIDTH/2, HEIGHT/2);
        boids.push_back(b);
        // output initial positions
        b.output(out);
    }

    while (true) {
        if (should_exit) {
            // cout << "continue..." << endl;
            out.close();
            exit(0);
        }
        // move boids TODO: PARALLELIZE
        for (int i = 0; i < boids.size(); i++) {
            boids[i].update();
        }

        // output their positions
        for (int i = 0; i < boids.size(); i++) {
            boids[i].output(out);
        }
    }
    out.close();
}

vector<float> values_for_string (string input) {
    istringstream iss(input);
    string s;
    vector<float> values;
    while ( getline( iss, s, ' ' ) ) {
        values.push_back(stof(s));
    }

    return values;
}

void display_boids(float count) {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Boids");

    vector<sf::CircleShape> shapes;
    for (int i = 0; i < count; i++) {
      sf::CircleShape shape(10.f);
      shape.setPosition(WIDTH/2, HEIGHT/2);
      shapes.push_back(shape);
    }

    ifstream data_file ("data.txt");

    while (window.isOpen())
    {
        // if (should_exit) {
        //     cout << "Exiting..." << endl;
        //     exit(0);
        // }
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        // draw the shapes
        for (int i = 0; i < shapes.size(); i++) {
            string line;
            getline(data_file, line);
            vector<float> values = values_for_string(line);

            shapes[i].setPosition(values[0], values[1]);
            window.draw(shapes[i]);
        }

        window.display();
    }

    return;
}
