#pragma once
#include <GUI/TabPage.hpp>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>
#include <vector>

namespace GUI {
    class TabContainer: public Widget{
        public:
            void check_status();
            void render(SDL_Renderer* ctx);
            void set_evento(SDL_Event e);
            void append(GUI::TabPage * page);
            void render();
        private:
            int index;
            std::vector<GUI::TabPage *> tabs;
    };
};