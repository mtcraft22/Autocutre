
#include "mtcad/materials.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_atomic.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <GUI/callback.hpp>
#include <unordered_map>
#include <utility>

namespace GUI {
    typedef enum event_type {CLICK,HOVER,HOVER_RELEASE} Events_types ;
    class Widget {
        public:
            virtual void check_status() = 0;
            virtual void render(SDL_Renderer* ctx) = 0;
            template<typename Widget, typename T>
            void set_event(Events_types type, Callback<Widget, T> call){
                callbacks_table.emplace(std::pair<Events_types, callback*>(type, new callback(call)))
            }

            SDL_Event e;
            
            ~Widget(){
                for (auto call :  callbacks_table){
                    delete call.second;
                }
            }
        private:
            std::unordered_map<Events_types,callback*> callbacks_table;


    };
}
