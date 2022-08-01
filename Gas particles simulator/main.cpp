#include <iostream>
#include "Position.cpp"
#include "Velocity.cpp"
#include "Particle.cpp"
#include "Simulator.cpp"
#include <sys/time.h>
#include <ctime>
#include "math.h"
#include <unistd.h>
#include "Graphics.cpp"
#include "SDL2.framework/Headers/SDL.h"
#include <fstream>


using namespace std;

Graphics* game = nullptr;


int main(int argc, char * argv[]) {
    Uint32 time, time0 = SDL_GetTicks();
    int frame_time;
    int frame_delay = 1000 / 60;
    
    game = new Graphics();
    game -> initialize();
    
    
    while (game -> running) {
        time = SDL_GetTicks();
        
        if(time - time0 > 20000){
            time0 = time;
            game -> simulator.save_velocities();
        }
        
        game -> handle_event();
        game -> update();
        game -> render();
        
        frame_time = SDL_GetTicks() - time;
        
        if(frame_delay > frame_time){
            SDL_Delay(frame_delay - frame_time);
        }
    }
    
    game -> clean();

}
