#pragma once

namespace GUI {
    class Events {
        public:
            static const int CLICK = 0x001;
            static const int HOVER = 0x002;
            static const int HOVER_RELEASE = 0x003;
    };
    class Image_events : public Events{
        public:
            static const int IMAGE_CHANGED = 0x101;
    };
    class Tab_Container_events:public Events {
        public:
            static const int TAB_CHANGED = 0x201;
            
            static const int TAB_ADDED = 0x202;
            static const int TAB_REMOVED = 0x203;

            static const int TAB_ITEM_REMOVED = 0x204;
            static const int TAB_ITEM_ADDED = 0x205;
    };
    class Text_events:public Events{
        static const int KEY_PRESS = 0x301;
    };
}


