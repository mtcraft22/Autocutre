
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_atomic.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include <iterator>
#include <ostream>
#include <vector>
#include <GUI/callback.hpp>
#include <unordered_map>
#include <utility>
#include <GUI/events.hpp>

namespace GUI {

    //creamos classe widgets para la tecnica del polimorfismo
    //para los contenedores
   
    class Widget {
        public:
            bool listen_events = false;
            virtual void render(SDL_Renderer* ctx) {this->listen_events=true;};
            virtual void set_evento(SDL_Event e) = 0; // notificamos evento
            
             /* disparamos los eventos llamando a la función asignada 
            los eventos CLICK , HOVER y HOVER_RELEASE son comunes para todos los widgets
             */
           virtual void check_status(){
                if(listen_events){

               
                bool prev = this->hover;
                this->hover = false;
                this->pressed = false;
                this->hover = 
                    (this->e.motion.x > this->box.x && this->e.motion.x < this->box.x+ (this->box.w)) 
                        && 
                    (this->e.motion.y > this->box.y && this->e.motion.y < this->box.y + (this->box.h))
                ;


                if (this->e.type == SDL_MOUSEBUTTONDOWN){
                  
                        this->pressed = this->hover && this->e.button.button == SDL_BUTTON_LEFT ;
                            
                }
                if (prev && !hover){
                    
                        auto call = this->get_event(HOVER_RELEASE);
                        if(call){
                                (*call)();
                        }

                    
                }else{

                    if(this->hover && !this->pressed){
                                auto call = this->get_event(HOVER);
                                if(call){
                                    (*call)();
                                }
                    }
                }

                if(this->pressed){
                    
                        auto call = this->get_event(CLICK);
                        std::cout << "hola" << " " << this->box.x << std::endl;
                        if(call){
                                (*call)();
                        }
                }
                }
            }

            template<typename Widget, typename T>
            void set_event(Events_t type, Callback<Widget, T> call){ // establecemos el evento
  				   
                auto c = new Callback(call);
                    callbacks_table.emplace(std::pair<Events_t, callback*>(type,c));
                }
                callback* get_event (Events_t event_type){
                    callback* event = this->callbacks_table[event_type];
                    if (event){
                        return event;
                    }else{
                        return nullptr;
                    }
			}
            Widget(){
                Widget::widgets.push_back(this);
            }
            ~Widget(){
                for (auto call :  callbacks_table){
                    delete call.second;
                }
            }
            static void notifyEventUpdate(SDL_Event e){
                for (auto w : Widget::widgets){
                    w->set_evento(e);
                }
            };
            void getPos(int& x, int& y){
                x = this->box.x;
                y = this->box.y;
            }
			void setPos(int x, int y){
                this->box.x=x;
                this->box.y=y;
  
            }
			void getColor(SDL_Color& color, SDL_Color& colortext){
                color = this->bg;
                colortext = this->fg;
            }
			void setColor(SDL_Color color, SDL_Color colortext){
                this->bg =color;
                this->fg = colortext;
            }
            SDL_Rect get_box(){return this->box;}
            void set_box(SDL_Rect box){this->box = box;}
        protected:
         
            SDL_Rect box;
            SDL_Color bg , fg;
            SDL_Event e;
        private:
            bool hover, pressed;
            static std::vector<Widget *> widgets;
           
            std::unordered_map<Events_t,callback*> callbacks_table;
    };
    
}
