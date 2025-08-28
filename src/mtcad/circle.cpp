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
#include <SDL2/SDL_stdinc.h>
#include <fstream>
#include <iostream>
#include <iterator>
#include <ostream>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "mtcad/materials.hpp"
#include <SDL2/SDL.h>
#include <mtcad/circle.hpp>
#include <cmath>
#include <cstdlib>
#include <mtcad/Node.hpp>
#include <stdexcept>
#include <vector>

const mt_cad::Materials_t mt_cad::Circle::material = mt_cad::CIRCLE;
const int mt_cad::Circle::max_nodes = 2;
mt_cad::Materials_t mt_cad::Circle::get_material(){
    return material ;
}
mt_cad::Circle::Circle(std::vector<Node> nodes){

    if (nodes.size()>=this->max_nodes){
        float x;
        float y;
        nodes.at(0).get_coords(x, y);

        this->nodes = nodes;
    }else{
        throw std::length_error("Too few nodes for a circle");
    }
}
std::vector<mt_cad::Node> mt_cad::Circle::get_points() {
	return this->nodes;
}
void mt_cad::Circle::set_points(std::vector<mt_cad::Node> nodes, bool make_center) {
	if (nodes.size()>=this->max_nodes){
        float x,y;
        nodes.at(0).get_coords(x,y);
       
        this->nodes = nodes;
    }else{
    SDL_Point prev = {0,0};
        throw std::length_error("Too few nodes for a circle");
    }
}
void mt_cad::Circle::draw(SDL_Renderer *ctx)
{
    float x1,y1,x2,y2;

    this->nodes.at(0).get_coords(x1,y1);
    this->nodes.at(1).get_coords(x2,y2);
    this->nodes.at(1).set_canmove(XY);
    this->nodes.at(1).set_coords(x2, y1);
    this->nodes.at(1).set_canmove(X);
    int radius = abs(x1 - x2);
    SDL_Point prev = {0,0};
    
    prev.x = cos(0)*radius+x1;
    prev.y = sin(0)*radius+y1;
   
    for (int i = 0 ; i<= 360; i+=2){
        
      
        SDL_RenderDrawLine(ctx, prev.x, prev.y, cos(((float)i/180)*3.1416)*radius+x1,sin(((float)i/180)*3.1416)*radius+y1);

        prev.x = cos(((float)i/180)*3.1416)*radius+x1;
        prev.y = sin(((float)i/180)*3.1416)*radius+y1; 
    }
   
}

bool mt_cad::Circle::hover(int x , int y){
    float x1,y1,x2,y2 = 0;
    this->nodes.at(0).get_coords(x1,y1);
    this->nodes.at(1).get_coords(x2,y2);

    int radius = abs(x1 - x2);
    int dist =  abs(x-x1) * abs(x-x1) +  abs(y-y1) * abs(y-y1);
    return dist <= (radius*radius);
};


