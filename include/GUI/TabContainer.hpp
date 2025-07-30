#pragma once
#include "GUI/Widget.hpp"
#include "GUI/callback.hpp"
#include "GUI/events.hpp"
#include <GUI/TabPage.hpp>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <ostream>
#include <utility>
#include <vector>

namespace GUI {
    class TabContainer: public Widget{
        public:
            TabContainer(){};
            
   
            void render(SDL_Renderer* ctx){
                int x = tabs.at(0)->box.x;
                for (auto tab : this->tabs){
                    int prevx = tab->tittle_box.x;
                    tab->tittle_box.x += x;
                    tab->tittle_box.x -= prevx;
                    tab->render_tittle(ctx);
                    x += tab->tittle_box.w+10;
                    tab->listen_events = false;
                    for (auto child : tab->chidren ){
                            child->listen_events = false;
                    }
                }
                if (this->index >= 0 && this->index < this->tabs.size()){
                  
                    this->tabs.at(this->index)->set_bg_tittle_color({0,0,200,255});
                    this->tabs.at(this->index)->render(ctx);
                    this->tabs.at(this->index)->set_bg_tittle_color({0,0,130,255});
                }
            };
            void set_evento(SDL_Event e){
                GUI::Widget::e = e;
                this->check_status();
            };
            void append(GUI::TabPage * page){
                page->listen_events = false;
                this->tabs.push_back(page);
                //std::cout << this->tabs[this->tabs.size()-1]->name<< std::endl;
                page->set_event(TAB_TITLE_CLICK,GUI::Callback(this,TabContainer::set_index));

            };
            template<typename Widget=GUI::TabContainer, typename T>
            void set_event(GUI::Events_t type, GUI::Callback<Widget, T> call) {
                call.set_buton(*(this));
                GUI::Widget::set_event(type, call);
            }
            static void set_index(TabPage &target,TabContainer &obj){
                std::cout << target.name << std::endl;
                obj.index = std::find(obj.tabs.begin(),obj.tabs.end(),&target) - obj.tabs.begin();
                std::cout << obj.index << std::endl;
            }
        private:
            int index = 0;
            std::vector<GUI::TabPage *> tabs;
    };
};