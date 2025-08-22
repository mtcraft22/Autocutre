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

#include <ostream>
#include <string>

#include <vector>

namespace GUI {
    class TabContainer: public Widget{
        public:
            TabContainer(){
                set_propertie(SELECTED_TAB_BG_COLOR, "0,0,255,255");
                set_propertie(SELECTED_TAB_FG_COLOR, "255,255,255,255");
                set_propertie(BG_TITTLE, "0,0,130,255");
                set_propertie(BG_COLOR, "0,255,0,255");
            };
            
   
            void render(SDL_Renderer* ctx){
                int x = tabs.at(0)->box.x;
                for (auto tab : this->tabs){
                    int prevx = tab->tittle_box.x;
                    tab->tittle_box.x += x;
                    tab->tittle_box.x -= prevx;
                    tab->render_tittle(ctx);
                    x += tab->tittle_box.w+3;
                    tab->listen_events = false;
                    for (auto child : tab->chidren ){
                            child->listen_events = false;
                    }
                }
                if (this->index >= 0 && this->index < this->tabs.size()){
                    auto prev = this->tabs.at(this->index)->get_propertie(BG_TITTLE);
                    this->tabs.at(this->index)->set_propertie(BG_TITTLE,get_propertie(SELECTED_TAB_BG_COLOR));
                    this->tabs.at(this->index)->set_propertie(BG_COLOR,get_propertie(BG_COLOR));
                    this->tabs.at(this->index)->render(ctx);
                    this->tabs.at(this->index)->set_propertie(BG_TITTLE,prev);
                }
            };
            void set_evento(SDL_Event e){
                GUI::Widget::e = e;
                this->check_status();
            };
            GUI::TabPage & operator <<(GUI::TabPage * page){
                page->listen_events = false;
                this->tabs.push_back(page);
                //std::cout << this->tabs[this->tabs.size()-1]->name<< std::endl;
                page->set_event(TAB_TITLE_CLICK,GUI::Callback(this,TabContainer::set_index));
                return *page;
            }
            GUI::TabPage & operator <<(GUI::TabPage & page){
                page.listen_events = false;
                this->tabs.push_back(&page);
                //std::cout << this->tabs[this->tabs.size()-1]->name<< std::endl;
                page.set_event(TAB_TITLE_CLICK,GUI::Callback(this,TabContainer::set_index));
                return page;
            };
            void operator<<(SDL_Color col){
                this->bg_color = col;
            }
            TabPage* operator[](int index){
                return this->tabs.at(index);
            }
            TabPage* operator[](TabPage * index){
                auto _find = std::find(this->tabs.begin(),this->tabs.end(),index);
                if  (_find!= this->tabs.end()){
                    return *_find.base();
                }else{
                    return nullptr;
                }
            }
            TabPage* operator[](std::string name){
                for (auto page : this->tabs){
                    if (page->name  == name){
                        return page;
                        break;
                    }
                }
                return nullptr;
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
            SDL_Color bg_color;
            int index = 0;
            std::vector<GUI::TabPage *> tabs;
    };
};