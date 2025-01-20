#pragma once

namespace GUI {
    template<typename Widget , typename T>
    class Callback{
        private:
            T* userdata;
            Widget* button;
            void (*call)(Widget& bot , T& userdata);
        public:
            Callback<Widget,T>();
            void set_callback(void (*call)(Widget& bot , T& userdata));
            void operator()();
            void set_buton(Widget& button);
            void set_userdata(T& userdata);
    };
}
