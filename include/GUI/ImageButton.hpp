#pragma once
#include "Boton.hpp"
#include "GUI/events/callback.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
namespace GUI {
    
    class ImageButton : public GUI::Boton{
        private:
            SDL_Texture * img;
            Callback<ImageButton, class T> click ;
            Callback<ImageButton, class T> hover ;
            Callback<ImageButton, class T> hover_release ;
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
            template<typename C>
            void set_click_callback (Callback<ImageButton, C> callback){
                callback.set_buton(*(this));
                this-> = new Callback(callback);
                
            }
            template<typename H>
            void set_hover_callback (Callback<ImageButton, H> callback){
                callback.set_buton(*(this));
                this->on_hover =new Callback(callback);
            }
            template<typename Hr>
            void set_hover_release_callback (Callback<ImageButton, Hr> callback){
                callback.set_buton(*(this));
                this->on_hover_release =new Callback(callback);
            }
            void render(SDL_Renderer* ctx);
    };
}
