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

#include <mtcad/Shape.hpp>
#include <mtcad/Node.hpp>
#include <SDL2/SDL_render.h>
#include <vector>
namespace mt_cad {
    class Line : public mt_cad::Shape{
        public:
            Line(std::vector<mt_cad::Node> nodes);
            void draw(SDL_Renderer * txt) ;
            bool hover(int x , int y) ;
            std::vector<mt_cad::Node> get_points() ;
            void set_points(std::vector<mt_cad::Node> nodes) ;
            static const int max_nodes;
            static const std::string material;
    };
}
