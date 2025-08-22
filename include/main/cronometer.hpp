#pragma  once
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>

class Cronometer{
    private:
        int _start;
        int _end;
    public:
        Cronometer();
        int get_time();
        void reset();
        
};