#pragma once

#include <SDL2/SDL_events.h>
#include <map>

class Event_callback {
    private:
        typedef void (*call)(SDL_Event e);
    public:
        static std::map<SDL_EventType,  call> events;
        static std::map<SDL_EventType,  call> window_events;

};