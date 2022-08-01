#ifndef VECTOR_H
#define VECTOR_H
#include "Vector.hpp"
#include "math.h"
#include <string>


using namespace std;

class Vector{
public:
    double x;
    double y;
    double magnitude;
    
    Vector(){};
    ~Vector(){};
    
    Vector(double _x, double _y){
        x = _x;
        y = _y;
        set_magnitude(_x, _y);
    }

    void set_magnitude(double _x, double _y){
        magnitude = sqrt(_x*_x + _y*_y);
    }

    //gives a string as output to use in printing the vector
    string print_vector(){
        char str[20];
        sprintf(str, "[%.4f , %.4f]", x, y);
        return (string) str;
    }


    //projects this vector on vector (a) and gives the vector as output
    Vector proj_on(Vector a){
        double _x, _y, multiplier = dot_product(*this, a) / pow(a.magnitude, 2);
        _x = multiplier * a.x;
        _y = multiplier * a.y;
        return Vector(_x, _y);
    }


    //adds or subtracts two vectors
    static Vector addition(Vector a, Vector b, int subtract){ // subtract = 0 -> addition , subtract = 1 -> subtraction
        if(subtract == 0) return Vector(a.x + b.x, a.y + b.y);
        return Vector(a.x - b.x, a.y - b.y);
    }


    //returns the dot product of two vectors
    static double dot_product(Vector a, Vector b){
        return a.x*b.x + a.y*b.y;
    }
    
    void scalar_product(double a){
        x *= a;
        y *= a;
    }

};


#endif
