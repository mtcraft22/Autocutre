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
#include "mtcad/materials.hpp"
#include <mtcad/Node.hpp>
#include <mtcad/Shape.hpp>
#include <SDL2/SDL_rect.h>
#include <mtcad/Rectangle.hpp>
#include <SDL2/SDL_render.h>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <stdexcept>
#include <vector>

const mt_cad::Materials_t mt_cad::Rectangle::material = RECTANGLE;
const int mt_cad::Rectangle::max_nodes = 2;

mt_cad::Rectangle::Rectangle(std::vector<mt_cad::Node> nodes){
    
    if (nodes.size() == 2){
        float x2,y2,x1,y1;
        nodes.at(0).get_coords(x1,y1);
	    nodes.at(1).get_coords(x2,y2);
        mt_cad::Node Central = mt_cad::Node(x1 + ((x2-x1)/2) ,y1 + ((y2-y1)/2),XY);
        this->nodes = {Central , nodes.at(0), nodes.at(1)};
    }else {
        throw std::length_error("Too much nodes for a rectangle shape");
    }
    
    
}
void mt_cad::Rectangle::draw(SDL_Renderer * ctx){
    float x2,y2,x1,y1;
    this->nodes.at(1).get_coords(x1,y1);
	this->nodes.at(2).get_coords(x2,y2);
    SDL_FPoint  points [5]={x1,y1,x1,y2,x2,y2,x2,y1,x1,y1};
    SDL_RenderDrawLinesF(ctx,points , 5);

    
}
bool mt_cad::Rectangle::hover(int x, int y){
    float x2,y2,x1,y1;
    this->nodes.at(1).get_coords(x1,y1);
	this->nodes.at(2).get_coords(x2,y2);
    SDL_FRect rect = {x1,y1,x2-x1,y2-y1};

    if (x2 < x1){
        int x3 = x1;
        x1 = x2;
        x2 = x3;
    }

    if (y2 < y1){
        int y3 = y1;
        y1 = y2;
        y2 = y3;
    }
    return (x > x1 && x < x2) && (y > y1 && y < y2) ;
    
}
void mt_cad::Rectangle::set_points(std::vector<mt_cad::Node> nodes, bool make_center){
     if (nodes.size() >= 2){
        float x2,y2,x1,y1;
        nodes.at(1).get_coords(x1,y1);
	    nodes.at(2).get_coords(x2,y2);
        mt_cad::Node Central = mt_cad::Node(0,0,XY);
        
        if(make_center){
            Central = mt_cad::Node(x1 + ((x2-x1)/2) ,y1 + ((y2-y1)/2),XY);
        }else{
            Central =  nodes.at(0);
        }
        this->nodes = {Central , nodes.at(1), nodes.at(2)};
    }else {
        throw std::length_error("Too much nodes for a rectangle shape");
    }
}
std::vector<mt_cad::Node> mt_cad::Rectangle::get_points(){
    return this->nodes;
}