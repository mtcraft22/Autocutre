#include "GUI/Widget.hpp"
#include <GUI/TabPage.hpp>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>
#include <iterator>
#include <string>

GUI::TabPage::TabPage(std::string name,SDL_Rect box){
    TTF_Font  * font = TTF_OpenFont(std::string(std::string(SDL_GetBasePath()) +"res/fonts/calibri.ttf").c_str(), 14);
    this->name = name;
    this->set_bg_color(SDL_Color {0,0,255,255});
    this->set_bg_tittle_color(SDL_Color {0,0,255,255});
    this->set_fg_tittle_color(SDL_Color{255,255,255,255});
    this->box = box;
    this->tittle = *(TTF_RenderText_Shaded(font, name.c_str(), this->fg, this->bg));
}

void GUI::TabPage::add_child(GUI::Widget & child){
    this->chidren.push_back(&child);
}
void GUI::TabPage::remove_child(GUI::Widget & child){
    
    auto victim = std::find(this->chidren.begin(),this->chidren.end(),child);
    if (victim != this->chidren.end()){
        this->chidren.erase(victim);
    }
}
void GUI::TabPage::remove_child(int index){
    if (index> 0 && index < this->chidren.size()){
        auto victim = std::find(this->chidren.begin(),this->chidren.end(),this->chidren.at(index));
        if (victim != this->chidren.end()){
            this->chidren.erase(victim);
        }
    }
}