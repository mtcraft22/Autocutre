#pragma once 
#include <mtcad/mtcad.hpp>

namespace mt_cad {
    class Ellipse : public mt_cad::Circle{
        public:
            static const int max_nodes;
            static const mt_cad::Materials_t material;
            Ellipse(std::vector<Node> nodes);
            void draw(SDL_Renderer * ctx) override;
            bool hover(int x , int y)override;
    };
} 