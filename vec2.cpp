#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include "Vec2.h"

//setting a vector
void Vec2::set(float i, float j) {
    x = i;
    y = j;
}


//adds two vectors
void Vec2::addV(Vec2 v) {
    x += v.x;
    y += v.y;
}

//adds some scalar, s, to vector
void Vec2::addS(float s) {
    x += s;
    y += s;
}

//subtracts some scalar, s, from vector
void Vec2::subS(float s) {
    x -= s;
    y -= s;
}

Vec2 Vec2::subtract(Vec2 v1, Vec2 v2) {
    Vec2 resultV;
    resultV.set((v1.x - v2.x),(v1.y - v2.y));
    return resultV;
}

void Vec2::multiplyV(Vec2 v) {
    x *= v.x;
    y *= v.y;
}

void Vec2::multiplyS(float s) {
    x *= s;
    y *= s;
}

void Vec2::divideV(Vec2 v) {
    x /= v.x;
    y /= v.y;
}

void Vec2::divideS(float s) {
    x /= s;
    y /= s;
}

float Vec2::distance(Vec2 v) const {
    float dist;
    float val1;
    float val2;
    val1 = pow((x-v.x), 2);
    val2 = pow((y-v.y), 2);
    dist = sqrt(val1 + val2);
    return dist;
}

float Vec2::dot(Vec2 v) const {
    float resultS;
    float val1;
    float val2;
    val1 = x*v.x;
    val2 = y*v.y;
    resultS = val1+val2;
    return resultS;
}

float Vec2::magnitude() const {
    return sqrt(pow(x, 2) + pow(y, 2));;
}

void Vec2::setMagnitude(float m) {
    normalize();
    multiplyS(m);
}

float Vec2::angle(Vec2 v) {
    //cos(angle) = (u.dot(v))/(magnitude(u)*magnitude(v))
    //angle = acos(u.dot(v))/(magnitude(u)*magnitude(v))
    float dot = (x*v.x) + (y*v.y);
    float mag1 = sqrt(pow(x,2) + pow(y,2));
    float mag2 = sqrt(pow(v.x, 2) + pow(v.y, 2));
    return acos(dot/mag1*mag2);
}

void Vec2::normalize() {
    float mag = magnitude();
    if (mag > 0) {
        set(x / mag, y / mag);
    } else {
        set(x, y);
    }
}

Vec2 Vec2::copy(Vec2 v) {
    Vec2 copy(v.x, v.y);
    return copy;
}
