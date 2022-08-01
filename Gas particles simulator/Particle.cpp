#ifndef PARTICLE_H
#define PARTICLE_H
#include "Particle.hpp"
#include "Position.cpp"
#include "Velocity.cpp"
#include "Vector.cpp"
#include "math.h"
#include <iostream>

using namespace std;

#define H 1200
#define W 1800

class Particle{
public:
    Position position;
    Velocity v;
    double radius;
    double mass;
    
    Particle(){};
    ~Particle(){};
    Particle(double x, double y, double vx, double vy, double r, double m){
        position = Position(x, y);
        v = Velocity(vx, vy);
        radius = r;
        mass = m;
    }
    
    //prints particle using print_vector()
    void print_particle()
    {
        cout << "position = " << position.print_vector() << "  -  velocity = " << v.print_vector() << endl;
    }
    
    //check if this particle and a given particle overlap
    bool check_overlap(Particle particle){
        double distance = Vector::addition(this -> position, particle.position, 1).magnitude;
        
        if(distance < radius + particle.radius) return true;
        
        return false;
    }
    
    int check_border(){
        double x_min = this -> position.x;
        double x_max = this -> position.x + this -> radius;
        double y_min = this -> position.y;
        double y_max = this -> position.y + this -> radius;
        
        if(x_min < 0) return 4;
        
        if(x_max > W) return 2;
        
        if(y_min < 0) return 1;
        
        if(y_max > H) return 3;
        
        return 0;
    }
    
    
    void collide_border(int border){
        if(border == 1 && this -> v.y < 0)
        {
            this -> v.y *= -1.0;
            this -> position.y = 0;
        }
    
        if(border == 2 && this -> v.x > 0)
        {
            this -> v.x *= -1.0;
            this -> position.x = W - 2.0 * this -> radius;
        }
        
        if(border == 3 && this -> v.y > 0)
        {
            this -> v.y *= -1.0;
            this -> position.y = H - 2.0 * this -> radius;
        }
        
        if(border == 4 && this -> v.x < 0)
        {
            this -> v.x *= -1.0;
            this -> position.x = 0;
        }
    }
    
    
    void update_position(){
        position = Vector::addition(position, v, 0);
        int _border = this -> check_border();
        if(_border != 0) this -> collide_border(_border);
        
    }
    
    
    bool check_particle_collision(Particle particle){
        Vector rel_r = Vector::addition(particle.position, this -> position, 1);
        Vector rel_v = Vector::addition(particle.v, this -> v, 1);
        Vector next_r = Vector::addition(rel_r, rel_v, 0);
        
        if(next_r.magnitude < particle.radius + this -> radius) return true;
        
        return false;
    }
    
    void collide_particle(Particle* particle){
        Vector rel_r = Vector::addition(particle -> position, this -> position, 1);
        Vector rel_v = Vector::addition(particle -> v, this -> v, 1);
        Vector del_1 = rel_v.proj_on(rel_r), del_2 = rel_v.proj_on(rel_r);
        del_1.scalar_product(2 * this -> mass / (this -> mass + particle -> mass));
        del_2.scalar_product(2 * particle -> mass / (this -> mass + particle -> mass));
        
        particle -> v = Vector::addition(particle -> v, del_1, 1);
        this -> v = Vector::addition(this -> v, del_2, 0);
    }
};

#endif
