#pragma once
#include "Boton.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
namespace GUI {
    
    class ImageButton : public GUI::Boton{
        private:
            SDL_Texture * img;
        public:
            ImageButton(
                SDL_Texture* img,
                int x,int y,
                SDL_Color color, 
                SDL_Color colortext, 
                std::string text, 
                SDL_Event *e
            );
            
            void render(SDL_Renderer* ctx);
    };
}
