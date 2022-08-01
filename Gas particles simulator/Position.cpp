#ifndef POSITION_H
#define POSITION_H
#include "Position.hpp"
#include "math.h"
#include "Vector.cpp"


//position is a child of class vector
class Position : public Vector{
public:
    
    Position(){}
    ~Position(){};
    Position(double pos_x, double pos_y) : Vector(pos_x, pos_y){}
    
    void operator=(Vector vec){
        x = vec.x;
        y = vec.y;
    }
    

};

#endif

