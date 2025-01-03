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
#include <SDL2/SDL_render.h>
#include <mtcad/Node.hpp>
#include <mtcad/line.hpp>
#include <stdexcept>
#include <vector>

const mt_cad::Materials_t mt_cad::Line::material = LINE;
const int mt_cad::Line::max_nodes = 2;
mt_cad::Line::Line(std::vector<mt_cad::Node> nodes){
    if (nodes.size() >= this->max_nodes){
        float x0,y0,x1,y1;
        nodes.at(0).get_coords(x0,y0);
        nodes.at(1).get_coords(x1,y1);
        if (x1 > x0){
            int x3 = x0;
            x0 = x1;
            x1 = x3;
        }
        if (y1 > y0){
            int y3 = y0;
            y0 = y1;
            y1 = y3;
        }
        mt_cad::Node central = {x0 + ((x1 - x0)/2), y0 + ((y1 - y0)/2),XY};
        this->nodes = {central, nodes.at(0), nodes.at(1)};
    }else {
        throw std::length_error("Too few nodes for a line");
    }
}
std::vector<mt_cad::Node> mt_cad::Line::get_points(){
    return this->nodes;
}
void mt_cad::Line::set_points(std::vector<mt_cad::Node> nodes, bool make_center){
   if (nodes.size() >= this->max_nodes){
        float x0,y0,x1,y1;
        nodes.at(1).get_coords(x0,y0);
        nodes.at(2).get_coords(x1,y1);
        if (x1 > x0){
            int x3 = x0;
            x0 = x1;
            x1 = x3;
        }
        if (y1 > y0){
            int y3 = y0;
            y0 = y1;
            y1 = y3;
        }
        mt_cad::Node central = mt_cad::Node(0,0,XY);
        if (make_center){
            central = {x0 + ((x1 - x0)/2), y0 + ((y1 - y0)/2),XY};
        }else {
            central = nodes.at(0);
        }
        
        this->nodes = {central, nodes.at(1), nodes.at(2)};
    }else {
        throw std::length_error("Too few nodes for a line");
    }
}
void mt_cad::Line::draw (SDL_Renderer * ctx){
	float x0,y0,x1,y1,x2,y2;
	this->nodes.at(1).get_coords(x0,y0);
	this->nodes.at(2).get_coords(x1,y1);
    SDL_RenderDrawLineF(ctx, x0, y0, x1, y1);
   
}
bool mt_cad::Line::hover(int x, int y){
	float x1,y1,x2,y2;
	this->nodes.at(1).get_coords(x1,y1);
	this->nodes.at(2).get_coords(x2,y2);
   

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
    SDL_FRect rect = {x1-5,y1-5,(x2-x1)+10,(y2-y1)+10};
    return (x > rect.x && x < rect.x+rect.w) && (y > rect.y && y < rect.y+rect.h) ;
}