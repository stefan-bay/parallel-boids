#ifndef VEC2_H_
#define VEC2_H_

class Vec2 {

public:
    float x;
    float y;

    Vec2() {

    }

    Vec2(float x_, float y_) {
        x = x_;
        y = y_;
    }

    void set(float x, float y);
    
    void addV(Vec2 v);
    void addS(float scalar);

    void subV(Vec2 v);
    void subS(float x);

    Vec2 subtract(Vec2 v1, Vec2 v2);

    void multiplyV(Vec2 v);
    void multiplyS(float x);

    void divideV(Vec2 v);
    void divideS(float x);

    float distance(Vec2 v) const;
    float dot(Vec2 v) const;
    float magnitude() const;
    void setMagnitude(float x);
    float angle(Vec2 v);
    void normalize();

    static Vec2 copy(Vec2 v);
    

};

#endif