#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

#include "Boid.h"
#include "Vec2.h"

Boid::Boid(float x, float y) {
    position = Vec2(x, y);
    velocity = Vec2((rand() % 3) - 2, (rand() % 3) - 2);
    acceleration = Vec2(0, 0);
}

void Boid::update() {
    position.addV(velocity);
    velocity.addV(acceleration);
}
