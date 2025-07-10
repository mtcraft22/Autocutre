#pragma once
#include <GUI/Widget.hpp>

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <vector>

namespace GUI {
    class TabContainer;
    class TabPage: public Widget{
        public:
            void check_status();
            void render(SDL_Renderer* ctx);
            void set_evento(SDL_Event e);
            void add_child(Widget & child);
            void remove_child(Widget & child);
            void remove_child(int index);
            TabPage(std::string name,SDL_Rect box);
            void set_bg_color(SDL_Color color);
            void set_bg_tittle_color(SDL_Color color);
            void set_fg_tittle_color (SDL_Color color);
            void set_border_color(SDL_Color color);
            void set_size(SDL_Rect box);
            void set_tittle_size(SDL_Rect box);
            friend class TabContainer;
        private:
            void render_tittle(); 
            TTF_Font * font;
            SDL_Surface tittle;
            std::string name;
            std::vector<GUI::Widget *> chidren;
            SDL_Color bg,bg_tittle,fg_tittle,border;
            int border_width;
            SDL_Rect tittle_box;
    };
};