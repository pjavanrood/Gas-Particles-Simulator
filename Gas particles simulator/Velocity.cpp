#ifndef VELOCITY_H
#define VELOCITY_H
#include "Velocity.hpp"
#include "math.h"
#include "Vector.cpp"

//velocity is a child of class vector
class Velocity : public Vector{
public:
    Velocity(){}
    ~Velocity(){}
    Velocity(double v_x, double v_y) : Vector(v_x, v_y){}
    
    void operator=(Vector vec){
        x = vec.x;
        y = vec.y;
        set_magnitude(x, y);
    }
        
};
#endif
