#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

#include "Boid.h"
#include "Vec2.h"

#include <iostream>
#include <fstream>

using namespace std;

Boid::Boid(float x, float y) {
    position = Vec2(x, y);

    float phi = 2 * M_PI * ((float)rand()/RAND_MAX);
    velocity = Vec2(.5 * cos(phi), .5 *sin(phi));

    acceleration = Vec2(0, 0);
}

void Boid::update() {
    position.addV(velocity);
    velocity.addV(acceleration);
}
