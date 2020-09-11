#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>

#include "Boid.h"
#include "Vec2.h"
#include "defaults.h"


#include <iostream>
#include <fstream>

using namespace std;

Boid::Boid(float x, float y) {
    position = Vec2(x, y);

    float phi = 2 * M_PI * ((float)rand()/RAND_MAX);
    velocity = Vec2(.5 * cos(phi), .5 *sin(phi));
    acceleration = Vec2(0, 0);

    max_speed = 3;
    max_force = .15;
}
void Boid::boundary_check() {
    // if (position.x > WIDTH) {
    //     float tmp = position.y;
    //     position.x = 0;
    //     position.y = HEIGHT - tmp;
    // }
    // if (position.y > HEIGHT) {
    //     float tmp = position.x;
    //     position.y = 0;
    //     position.x = WIDTH - tmp;
    // }
    // if (position.x < 0) {
    //     float tmp = position.y;
    //     position.x = WIDTH;
    //     position.y = HEIGHT - tmp;
    // }
    // if (position.y < 0) {
    //     float tmp = position.x;
    //     position.y = HEIGHT;
    //     position.x = WIDTH - tmp;
    // }
    if (position.x < 0) position.x += WIDTH;
	if (position.y < 0) position.y += HEIGHT;
	if (position.x > WIDTH) position.x -= WIDTH;
	if (position.y > HEIGHT) position.y -= HEIGHT;
}

Vec2 Boid::align(vector<Boid> boids) {
    float fov = 75;

    Vec2 total_force(0, 0);

    int visible_boids = 0;
    for (int i = 0; i < boids.size(); i++) {
        float distance = position.distance(boids[i].position);

        if (distance > 0 && distance < fov) {
            total_force.addV(boids[i].velocity);
            visible_boids++;
        }
    }

    if (visible_boids > 0) {
        total_force.divideS((float)visible_boids);
        total_force.normalize();
        total_force.multiplyS(max_speed);

        Vec2 steering_force = Vec2::subtract(total_force, velocity);
        steering_force.limit(max_force);
        return steering_force;
    } else {
        Vec2 zero(0, 0);
        return zero;
    }
}

Vec2 Boid::cohesion(vector<Boid> boids) {
    float fov = 50;

    Vec2 total_force(0, 0);

    int visible_boids = 0;
    for (int i = 0; i < boids.size(); i++) {
        float distance = position.distance(boids[i].position);

        if (distance > 0 && distance < fov) {
            total_force.addV(boids[i].position);
            visible_boids++;
        }
    }

    if (visible_boids > 0) {
        total_force.divideS((float)visible_boids);
        total_force.subV(position);
        total_force.normalize();
        total_force.multiplyS(max_speed);
        Vec2 steering_force = Vec2::subtract(total_force, velocity);
        steering_force.limit(max_force);
        return steering_force;
    } else {
        Vec2 zero(0, 0);
        return zero;
    }
}

Vec2 Boid::separation(vector<Boid> boids) {
    float fov = 50;

    Vec2 total_force(0, 0);

    int visible_boids = 0;
    for (int i = 0; i < boids.size(); i++) {
        float distance = position.distance(boids[i].position);

        if (distance > 0 && distance < fov) {
            Vec2 difference = Vec2::subtract(position, boids[i].position);
            difference.divideS(distance*distance);
            total_force.addV(difference);
            visible_boids++;
        }
    }

    if (visible_boids > 0) {
        total_force.divideS((float)visible_boids);
        // total_force.subV(position);
        total_force.normalize();
        total_force.multiplyS(max_speed);
        Vec2 steering_force = Vec2::subtract(total_force, velocity);
        steering_force.limit(max_force);
        return steering_force;
    } else {
        Vec2 zero(0, 0);
        return zero;
    }
}



void Boid::update(vector<Boid> boids) {
    boundary_check();

    // flocking

    Vec2 alignment_force = align(boids);
    acceleration.addV(alignment_force);
    Vec2 chsn = cohesion(boids);
    acceleration.addV(chsn);

    Vec2 sep = separation(boids);
    acceleration.addV(sep);

    // slow down acceleration
    acceleration.multiplyS(.35);

    // update boid position/velocity
    position.addV(velocity);
    velocity.addV(acceleration);
    velocity.limit(max_speed);

    // reset acceleration
    acceleration.multiplyS(0);
}
