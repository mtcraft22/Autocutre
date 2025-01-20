#pragma once
#include "Boton.hpp"
#include "GUI/callback.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
namespace GUI {
    
    class ImageButton : public GUI::Boton{
        private:
            SDL_Texture * img;
            Callback<ImageButton, class T> click = Callback<ImageButton, class T>();
            Callback<ImageButton, class T> hover = Callback<ImageButton, class T>();
            Callback<ImageButton, class T> hover_release = Callback<ImageButton, class T>();
        public:
            ImageButton(
                SDL_Texture *img, 
                int x, int y, 
                SDL_Color bg, 
                SDL_Color fg, 
                std::string text,
                SDL_Event *e,
                int gapy=0 , 
                int gapx =0
            );
       
            void render(SDL_Renderer* ctx);
    };
}
