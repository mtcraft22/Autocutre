#pragma once
#include "GUI/events.hpp"
#include <GUI/Widget.hpp>

#include <SDL2/SDL_error.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

namespace GUI {
    class TabContainer;
    class TabPage: public Widget{
        public:
            
            void render(SDL_Renderer* ctx) override{
                GUI::Widget::render(ctx);
                render_tittle(ctx);
                
                this->bg = get_color_propertie(BG_COLOR);

                SDL_SetRenderDrawColor(ctx, this->bg.r,this->bg.g,this->bg.b,this->bg.a);
                
                SDL_RenderFillRect(ctx, &box);
                for (auto w : this->chidren){
                  
                    w->render(ctx);
                   
                    
                };
           
                
            };
            //void set_evento(SDL_Event e);
          
            void set_size(SDL_Rect box){
                this->box = box;
            };
            //void set_tittle_size(SDL_Rect box);
            friend class TabContainer;

          
            

            TabPage(std::string name,SDL_Rect box){
                set_propertie(FONT_SIZE, "20");
                std::cout << get_propertie(FONT_SIZE) << std::endl;
                this->font = TTF_OpenFont(std::string(std::string(SDL_GetBasePath()) +"res/fonts/calibri.ttf").c_str(),std::atoi( get_propertie(FONT_SIZE).c_str()));
                this->name = name;
                 std::cout << get_propertie(FONT_SIZE) << std::endl;
                set_propertie(BG_COLOR ,"0,0,255,255");
                set_propertie(BG_TITTLE, "0,0,130,255");
                set_propertie(FG_TITTLE, "255,255,255,255");
                 set_propertie(FG_COLOR, "255,255,255,255");
                  std::cout << get_propertie(FONT_SIZE) << std::endl;
                this->box = box;
                
      
           
                
                this->tittle = TTF_RenderText_Shaded(this->font, name.c_str(), get_color_propertie(FG_TITTLE),get_color_propertie(BG_TITTLE));
                if (!tittle){
                    std::cout << SDL_GetError() << std::endl;
                    return;
                }
                tittle_box = {box.x,box.y-tittle->h,tittle->w,tittle->h};
              
                 std::cout << get_propertie(FONT_SIZE) << std::endl;
            }

            Widget& operator << (GUI::Widget &child){
                this->chidren.push_back(&child);
                auto call = this->get_event(Events_t::ADD_CHILDREN);
                if (call != nullptr){
                    (*call)();
                }
  

                    auto w_box = child.get_box();
                    int w_x = this->box.x+w_box.x;
                    int w_y = this->box.y-w_box.y;
                    child.setPos(w_x,w_y+this->tittle->h );
                return child;
            }
            Widget* operator[](int index){
                return this->chidren.at(index);
            }
            Widget* operator[](Widget * index){
                auto _find = std::find(this->chidren.begin(),this->chidren.end(),index);
                if  (_find!= this->chidren.end()){
                    return *_find.base();
                }else{
                    return nullptr;
                }
            }
            /*void remove_child(GUI::Widget & child){
                
              auto victim = std::find(this->chidren.begin(),this->chidren.end(),child);
                if (victim != this->chidren.end()){
                    this->chidren.erase(victim);
                    auto call = this->get_event(Events_t::REMOVE_CHILDREN);
                    if (call){(*call)();}
                }
            }
            void remove_child(int index){
                if (index>= 0 && index < this->chidren.size()){
                    auto victim = std::find(
                        this->chidren.begin(),
                        this->chidren.end(),
                        this->chidren.at(index)
                    );
                    if (victim != this->chidren.end()){
                        this->chidren.erase(victim);
                        auto call = this->get_event(Events_t::REMOVE_CHILDREN);
                        if (call){(*call)();}
                    }
                }
            }*/
            void set_bg_color(SDL_Color color){
                this->bg = color;
                
            }
            void set_bg_tittle_color(SDL_Color color){
                this->bg_tittle = color;
                this->tittle = TTF_RenderText_Shaded(this->font, name.c_str(), this->fg_tittle,this->bg_tittle);
            }
            void set_fg_tittle_color(SDL_Color color){
                this->fg_tittle = color;
                this->tittle = TTF_RenderText_Shaded(this->font, name.c_str(), this->fg_tittle,this->bg_tittle);
            }
            void set_border_color(SDL_Color color){
                this->border = color;
            }
            template<typename Widget=GUI::TabPage, typename T>
            void set_event(GUI::Events_t type, GUI::Callback<Widget, T> call) {
              
                call.set_buton(*(this));
                GUI::Widget::set_event(type, call);
            }
          void set_evento(SDL_Event e) override {
                this->GUI::Widget::e = e;
                this->check_status();
            }
            void check_status () override{
                GUI::Widget::check_status();
                
                    this->hover_tittle = 
                    (this->e.motion.x > this->tittle_box.x && this->e.motion.x < this->tittle_box.x+ (this->tittle_box.w)) 
                        && 
                    (this->e.motion.y > this->tittle_box.y && this->e.motion.y < this->tittle_box.y + (this->tittle_box.h));
                    
                    if (this->e.type == SDL_MOUSEBUTTONDOWN && hover_tittle){
                        auto call = this->get_event(TAB_TITLE_CLICK);
                        if(call){
                            (*call)();
                        }
                    }
                

            };
        ~TabPage(){

                 SDL_DestroyTexture(this->text);
     
                TTF_CloseFont(this->font);

               SDL_FreeSurface(this->tittle);
        }
        private:
            void render_tittle(SDL_Renderer * ctx){
               /* if(this->tittle){
                    SDL_FreeSurface(this->tittle);
                }*/
                TTF_SetFontSize(this->font,std::atoi(get_propertie(FONT_SIZE).c_str()));
                this->tittle = TTF_RenderText_Shaded(
                    this->font, this->name.c_str(),  
                    get_color_propertie(FG_TITTLE), 
                    get_color_propertie(BG_TITTLE));
                text = SDL_CreateTextureFromSurface(ctx, tittle);

               
                SDL_RenderCopy(ctx, text, NULL, &tittle_box);
             
            };
            bool hover_tittle;
            SDL_Texture * text;
            TTF_Font * font;
            SDL_Surface * tittle;
            std::string name;
            std::vector<GUI::Widget *> chidren;
            SDL_Color bg,bg_tittle,fg_tittle,border;
            int border_width;
            SDL_Rect tittle_box;
    };
};
