
#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_atomic.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>

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
            virtual void check_status() = 0; // disparamos los eventos llamando a la función asignada
            virtual void render(SDL_Renderer* ctx) = 0;
            virtual void set_evento(SDL_Event e) = 0; // notificamos evento
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
                x = this->x;
                y = this->y;
            }
			void setPos(int x, int y){
                this->x=x;
                this->y=y;
                this->box.x = x;
                this->box.y = y;
            }
			void getColor(SDL_Color& color, SDL_Color& colortext){
                color = this->bg;
                colortext = this->fg;
            }
			void setColor(SDL_Color color, SDL_Color colortext){
                this->bg =color;
                this->fg = colortext;
            }
        protected:
            int x, y;
            SDL_Rect box;
            SDL_Color bg , fg;
        private:
            
            static std::vector<Widget *> widgets;
            SDL_Event e;
            std::unordered_map<Events_t,callback*> callbacks_table;
    };
    
}
