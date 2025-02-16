#pragma once
#include <GUI/callback.hpp>
#include <iostream>
#include <ostream>
namespace GUI {
    class callback{
        public:
            virtual void operator()() = 0;
            ~callback(){};
    };
    template<typename Widget , typename T>
    class Callback: public GUI::callback{
        private:
            T* userdata;
            Widget* button;
            void (*call)(Widget& bot , T& userdata);
        public:
            
            Callback(){
                this->userdata = nullptr;
                this->button = nullptr;
            }

            void set_buton(Widget& button) {
                this->button = &button;
            }

            void set_userdata(T& userdata) {
                this->userdata = &userdata;
            }

            void operator()() override{
                if (this->call && this->button && this->userdata) {
                    this->call(*(this->button),*(this->userdata));
                }
            }

            void set_callback(void (*call)(Widget& bot , T& userdata)){
                this->call = call;
            }
    };
}