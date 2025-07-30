#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
const int ticksframe = 1000/3;
int main(int argc, char **argv){

    if(SDL_Init(SDL_INIT_EVERYTHING)<0){
        std::cout << SDL_GetError() << std::endl;
        return -1;
    }
    SDL_Window * window = SDL_CreateWindow("$1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
    SDL_Renderer * ctx = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    bool run;
    int start = SDL_GetTicks();
    int end = SDL_GetTicks();
    int delta;


    SDL_Event e;


    while (run) {
        
        start = SDL_GetTicks();
        delta = start-end;
        if ( delta > ticksframe){
            
        }else{
            SDL_Delay(ticksframe -delta);
        }

    }

    SDL_Quit();
    return 0;
}
