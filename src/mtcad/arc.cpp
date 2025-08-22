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

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <algorithm>
#include <mtcad/mtcad.hpp>
#include <stdexcept>
#include <vector>

const mt_cad::Materials_t mt_cad::Arc::material = mt_cad::materials::ARC;
const int mt_cad::Arc::max_nodes = 5;

mt_cad::Arc::Arc(std::vector<mt_cad::Node> nodes):mt_cad::Circle(nodes){
     if (nodes.size()>=this->max_nodes){
        float x,y;
        nodes.at(0).get_coords(x, y);
        float x2,y2,x3,y3;
        this->nodes = {nodes.at(0),nodes.at(1),nodes.at(2),nodes.at(3),nodes.at(4)};
    }else{
        throw std::length_error("Too few nodes for a circle");
    }
};
void mt_cad::Arc::draw(SDL_Renderer *ctx)
{
    float x1,y1,x2,y2,x3,y3,x4,y4,x5,y5 = 0;
    this->nodes.at(3).set_canmove(XY);
    this->nodes.at(0).get_coords(x1,y1);
    this->nodes.at(1).get_coords(x2,y2);
    this->nodes.at(2).get_coords(x3,y3);
    this->nodes.at(3).get_coords(x4,y4);
    this->nodes.at(4).get_coords(x5,y5);

    this->nodes.at(1).set_canmove(XY);
    this->nodes.at(2).set_canmove(XY);

    this->nodes.at(1).set_coords(x2, y1);
    this->nodes.at(2).set_coords(x1, y3);
    this->nodes.at(3).set_coords((x1+20), y4);
    this->nodes.at(4).set_coords((x1+40), y5);

    this->nodes.at(1).set_canmove(X);
    this->nodes.at(2).set_canmove(Y);
    this->nodes.at(3).set_canmove(Y);
    this->nodes.at(4).set_canmove(Y);

    int radius = abs(x1 - x2);
    int radius2 = abs(y1 - y3);
    SDL_Point prev = {0,0};
    

    angle_pos = 361 * (abs(y3-y4))/360;
    angle_pos2 = 361 * (abs(y3-y5))/360;
    prev.x = cos(angle_pos2)*radius+x1;
    prev.y = sin(angle_pos2)*radius2+y1;


    for (int i = angle_pos2 ; i<= angle_pos; i+=1){
        
        prev.x = cos(((float)i/180)*3.1416)*radius+x1;
        prev.y = sin(((float)i/180)*3.1416)*radius2+y1;
        SDL_RenderDrawLineF(ctx, prev.x, prev.y, cos(((float)i/180)*3.1416)*radius+x1,sin(((float)i/180)*3.1416)*radius2+y1);

    }
   
}
bool mt_cad::Arc::hover(int x , int y){
    float x1,y1,x2,y2,x3,y3 = 0;
    this->nodes.at(0).get_coords(x1,y1);
    this->nodes.at(1).get_coords(x2,y2);
    this->nodes.at(2).get_coords(x3,y3);
    int radius = abs(x1 - x2);
    int radius2 = abs(y1 - y3);
    int distx =  abs(x-x1); 
    int disty =   abs(y-y1) ;
    return distx < radius && disty < radius2;
};
