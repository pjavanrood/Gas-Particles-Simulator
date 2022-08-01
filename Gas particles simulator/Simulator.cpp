#ifndef SIMULATOR_H
#define SIMULATOR_H
#include "Simulator.hpp"
#include "Particle.cpp"
#include "Particle.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include "math.h"

using namespace std;

class Simulator{
public:
    int const HEIGHT = 1200;
    int const WIDTH = 1800;
    ofstream v_file;
    vector<Particle> particles;
    Simulator(){}
    ~Simulator(){}
    
    void initialize_particles(){
        double r = 10, mass = 1, vx, vy;
        
        for(int i = 0; i < 20; i++){
            for(int j = 0; j < 30; j++){
                vx = rand()%10;
                vy = rand()%10;
                int x_rand = rand() % 10;
                int y_rand = rand() % 10;
                if(x_rand >= 5) vx *= -1.0;
                if(y_rand >= 5) vy *= -1.0;
                this -> add_particle(Particle(i*90, j*40, vx, vy, r, mass));
            }
        }
        
        v_file.open("velocities.txt");
        save_velocities();
    }
    
    //adds a particle to the simulation, checks for overlaps and borders before adding
    void add_particle(Particle particle){
        if(particle.check_border() != 0){
            cout << "can not add particle, OUT OF BORDER!" << endl;
            particle.print_particle();
            return;
        }
        int overlap = check_overlap(particle);
        if(overlap != -1){
            cout << "can not add particle, OVERLAP!" << endl;
            particles[overlap].print_particle();
            particle.print_particle();
            return;
        }
        
        cout << "particle added successfully" << endl;
        particles.push_back(particle);
        
        
    }

    //prints all particles
    void print_particles(){
        int len = (int) particles.size();
        for(int i = 0; i < len; i++){
            cout << i << ":    ";
            particles[i].print_particle();
        }
    }
    
    
    //checks if a new particle that wants to be added has overlap with existing particles
    int check_overlap(Particle particle){
        int len = (int) particles.size();
        for(int i = 0; i < len; i++){
            if(particle.check_overlap(particles[i])) return i;
        }
        return -1;
    }
    
    
    //checks if a new particle that wants to be added is out of borders
    bool check_out_of_border(Particle particle){
        double x_min = particle.position.x - particle.radius;
        double x_max = particle.position.x + particle.radius;
        double y_min = particle.position.y - particle.radius;
        double y_max = particle.position.y + particle.radius;
        if(x_min < 0 || x_max > WIDTH || y_max > HEIGHT || y_min < 0) return true;
        return false;
    }
    
    void update_collisions(){
        int len = (int) particles.size();
        
        for(int i = 0; i < len - 1; i++){
            for(int j = i + 1; j < len; j++){
                if(particles[i].check_particle_collision(particles[j]))
                    particles[i].collide_particle(&particles[j]);
                
            }
        }
    }
    
    
    void update(){
        int len = (int) particles.size();
        for(int i = 0; i < len; i++){
            particles[i].update_position();
        }
    }
    
    
    double kinetic_energy(){
        double energy = 0;
        int len = (int) particles.size();
        for(int i = 0; i < len; i++){
            energy += pow(particles[i].v.magnitude, 2);
        }
        return energy;
    }
    
    void save_velocities(){
        int len = (int) particles.size();
        
        for(int i = 0; i < len; i++){
            v_file << particles[i].v.magnitude;
            if(i != len - 1)
                v_file << ",";
        }
        
        v_file << endl;
    }
};

#endif




