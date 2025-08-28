#pragma once
#include "mtcad/Node.hpp"
#include "mtcad/materials.hpp"
#include <mtcad/curve.hpp>
#include <vector>
namespace mt_cad {
    class Quadratic_curve : public mt_cad::Curve{
        public:
            static const int max_nodes;
            static const mt_cad::Materials_t material;
            Materials_t get_material() override;
            Quadratic_curve(std::vector<mt_cad::Node> nodes):mt_cad::Curve(nodes){}
            void draw(SDL_Renderer *ctx) override;
            bool hover(int x, int y) override;
    };
};
