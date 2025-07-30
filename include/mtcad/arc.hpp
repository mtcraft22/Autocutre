/*
    Copyright (C) 2024 mtcraft22(Marc Tort Pascual) 
    This file is part of Bezier.

    Bezier is free software: 
    you can redistribute it and/or modify it under the terms 
    of the GNU General Public License as published by the Free Software Foundation, 
    either version 3 of the License, or (at your option) any later version.
    Bezier is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
    without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
    See the GNU General Public License for more details.
    You should have received a copy of the GNU General Public License along with Bezier. If not, see <https://www.gnu.org/licenses/>. 
*/
#pragma once 
#include <mtcad/mtcad.hpp>

namespace mt_cad {
    class Arc : public mt_cad::Circle{
        public:
            int angle_pos,angle_pos2 = 0;
            static const int max_nodes;
            static const mt_cad::Materials_t material;
            Arc(std::vector<Node> nodes);
            void draw(SDL_Renderer * ctx) override;
            bool hover(int x , int y)override;
    };
} 


