#include <main/cronometer.hpp>

Cronometer::Cronometer(){
    _start = SDL_GetTicks();
    _end = SDL_GetTicks();
}
int Cronometer::get_time(){
    _end = SDL_GetTicks();
    return _end - _start;
};
void Cronometer::reset(){
    _end = _start;
};