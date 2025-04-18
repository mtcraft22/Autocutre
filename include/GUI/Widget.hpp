
#include "mtcad/materials.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_atomic.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include "GUI/events/callback.hpp"
#include <unordered_map>
#include <utility>
#include "GUI/events/events.hpp"

namespace GUI {

    //creamos classe widgets para la tecnica del polimorfismo
    //para los contenedores
   
    class Widget {
        public:
            virtual void check_status() = 0;
            virtual void render(SDL_Renderer* ctx) = 0;
            void set_evento(SDL_Event e){
                this->e = e;
            };
            template<typename Widget, typename T>
            void set_event(Events_t type, Callback<Widget, T> call){
  
                callbacks_table.emplace(std::pair<Events_t, callback*>(type,new Callback(call)));
            }
			callback* get_event (Events_t event_type){
				callback* event = this->callbacks_table[event_type];
				if (event){
					return event;
				}else{
					return nullptr;
				}
			}
            ~Widget(){
                for (auto call :  callbacks_table){
                    delete call.second;
                }
            }
        private:
            SDL_Event e;
            std::unordered_map<Events_t,callback*> callbacks_table;
    };
}
