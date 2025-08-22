#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
class Autocutre{
    public:
        static bool run;
        static SDL_Window * window;
        static SDL_Renderer * ctx;
        static SDL_Event * e;
        Autocutre();
        ~Autocutre();
};