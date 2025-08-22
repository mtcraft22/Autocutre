#include <SDL2/SDL_render.h>
#pragma once
class Grid_Texture{
    private:
        SDL_Texture * canvas;
    public:
        void render_grid(int sw,int sh,SDL_Texture *  canvas);
};