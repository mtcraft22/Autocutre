#include <GUI/callback.hpp>
#include <GUI/Boton.hpp>
#include <SDL2/SDL_events.h>

template<typename Widget , typename T>
GUI::Callback<Widget,T>::Callback(){
    this->userdata = nullptr;
    this->button = nullptr;
}
template <typename Widget , typename T>
void GUI::Callback<Widget,T>::set_buton(Widget& button){
    this->button = &button;
}
template<typename Widget , typename T>
void GUI::Callback<Widget,T>::set_userdata(T& userdata){
    this->userdata = &userdata;
}
template<typename Widget , typename T>
void GUI::Callback<Widget,T>::operator()(){
    if (this->call && this->button && this->userdata) {
        this->call(*(this->button),*(this->userdata));
    }
}
template<typename Widget , typename T>
void GUI::Callback<Widget,T>::set_callback(void (*call)(Widget& bot , T& userdata)){
    this->call = call;
}