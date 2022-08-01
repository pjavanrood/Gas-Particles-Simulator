#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "Graphics.hpp"
#include "SDL2.framework/Headers/SDL.h"
#include "Position.cpp"
#include "Particle.cpp"
#include "Simulator.cpp"
#include "math.h"
#include <iostream>


using namespace std;

class Graphics {
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    Simulator simulator;
    
    Graphics(){};
    ~Graphics(){};
    
    void initialize(){

        simulator.initialize_particles();
        
        
        if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
            cout << "System initialized" << endl;
            window = SDL_CreateWindow("Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1800, 1200, 0);
            renderer = SDL_CreateRenderer(window, -1, 0);
            
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
            
            if(window && renderer){
                running = true;
                cout << "window and renderer created" << endl;
                return;
            }
            
            cout << "!!window and renderer NOT created!!" << endl;
        }
        
        running = false;
    }
    
    void handle_event(){
        SDL_Event e;
        SDL_PollEvent(&e);
        if(e.type == SDL_QUIT || e.type == SDL_KEYDOWN) running = false;
    }
    
    void render(){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        
        SDL_RenderClear(renderer);
        
        draw_circles();
        
        SDL_RenderPresent(renderer);
    }
    
    void update(){
        simulator.update();
        simulator.update_collisions();
    }
    
    void clean(){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        simulator.save_velocities();
        simulator.v_file.close();
    }
    
    void draw_circles(){
        int len = (int) simulator.particles.size();
        for(int i = 0; i < len; i++){
            SDL_RenderFillCircle(renderer, simulator.particles[i]);
        }
    }
    
    
    
    void SDL_wait_key(){
            SDL_Event *e = new SDL_Event();
            while(e->type != SDL_KEYDOWN)
                SDL_PollEvent(e);
    }
    
    int SDL_RenderDrawCircle(SDL_Renderer * renderer, Particle particle)
    {
        int offsetx, offsety, d;
        int status;
        double x = particle.position.x, y = particle.position.y, radius = particle.radius;


        offsetx = 0;
        offsety = radius;
        d = radius -1;
        status = 0;
        
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);

        while (offsety >= offsetx) {
            status += SDL_RenderDrawPoint(renderer, x + offsetx, y + offsety);
            status += SDL_RenderDrawPoint(renderer, x + offsety, y + offsetx);
            status += SDL_RenderDrawPoint(renderer, x - offsetx, y + offsety);
            status += SDL_RenderDrawPoint(renderer, x - offsety, y + offsetx);
            status += SDL_RenderDrawPoint(renderer, x + offsetx, y - offsety);
            status += SDL_RenderDrawPoint(renderer, x + offsety, y - offsetx);
            status += SDL_RenderDrawPoint(renderer, x - offsetx, y - offsety);
            status += SDL_RenderDrawPoint(renderer, x - offsety, y - offsetx);

            if (status < 0) {
                status = -1;
                break;
            }

            if (d >= 2*offsetx) {
                d -= 2*offsetx + 1;
                offsetx +=1;
            }
            else if (d < 2 * (radius - offsety)) {
                d += 2 * offsety - 1;
                offsety -= 1;
            }
            else {
                d += 2 * (offsety - offsetx - 1);
                offsety -= 1;
                offsetx += 1;
            }
        }

        return status;
    }


    int SDL_RenderFillCircle(SDL_Renderer * renderer, Particle particle)
    {
        int offsetx, offsety, d;
        int status;
        double x = particle.position.x, y = particle.position.y, radius = particle.radius;

        
        offsetx = 0;
        offsety = radius;
        d = radius -1;
        status = 0;

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
        
        
        while (offsety >= offsetx) {

            status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx,
                                         x + offsety, y + offsetx);
            status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety,
                                         x + offsetx, y + offsety);
            status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety,
                                         x + offsetx, y - offsety);
            status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx,
                                         x + offsety, y - offsetx);

            if (status < 0) {
                status = -1;
                break;
            }

            if (d >= 2*offsetx) {
                d -= 2*offsetx + 1;
                offsetx +=1;
            }
            else if (d < 2 * (radius - offsety)) {
                d += 2 * offsety - 1;
                offsety -= 1;
            }
            else {
                d += 2 * (offsety - offsetx - 1);
                offsety -= 1;
                offsetx += 1;
            }
        }

        return status;
    }
};


#endif
