#ifndef BOID_H_
#define BOID_H_

#include "Vec2.h"

#include <iostream>
#include <fstream>

using namespace std;

class Boid {
public:
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

    float max_speed;
    float max_force;

    Boid (float x, float y);

    Vec2 align(vector<Boid> boids);

    void update(vector<Boid> boids);

private:
    void boundary_check();
    void turn();
};


#endif
