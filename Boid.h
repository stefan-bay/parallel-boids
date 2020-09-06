#ifndef BOID_H_
#define BOID_H_

#include "Vec2.h"

class Boid {
public:
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

    Boid (float x, float y);

    void update();
};

#endif
