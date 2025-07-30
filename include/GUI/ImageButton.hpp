#pragma once
#include "Boton.hpp"
#include "callback.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>
namespace GUI {
    
    class ImageButton : public GUI::Boton{
        private:

			SDL_Texture * img;

        public:
            ImageButton(
                SDL_Texture *img, 
                int x, int y, 
                SDL_Color bg, 
                SDL_Color fg,
                SDL_Event *e,
                int gapy = 0, 
                int gapx = 0
            );
           // void set_evento(SDL_Event e) override;
			template<typename Widget=GUI::ImageButton, typename T>
			void set_event(GUI::Events_t type, GUI::Callback<Widget, T> call) {
				call.set_buton(*(this));
				GUI::Widget::set_event(type, call);
			}
            void render(SDL_Renderer* ctx)override;
    };
}
