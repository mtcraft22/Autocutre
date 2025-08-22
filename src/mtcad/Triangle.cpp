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
#include "mtcad/materials.hpp"
#include <mtcad/Node.hpp>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <mtcad/Triangle.hpp>
#include <stdexcept>
#include <vector>


const mt_cad::Materials_t mt_cad::Triangle::material = TRIANGLE;
const int mt_cad::Triangle::max_nodes = 3;

mt_cad::Triangle::Triangle(std::vector<mt_cad::Node> nodes){
    if (nodes.size()>=this->max_nodes){
        float x0,y0,x1,y1,x2,y2;
        nodes.at(0).get_coords(x0,y0);
        nodes.at(1).get_coords(x1,y1);
        nodes.at(2).get_coords(x2,y2);
        mt_cad::Node central = mt_cad::Node(((x0+x1+x2)/3), ((y0+y1+y2)/3),XY);
        this->nodes = {central,nodes.at(0),nodes.at(1),nodes.at(2)};
    }else{
        throw std::length_error("Too many nodes for a curve");
    }
}
void mt_cad::Triangle::draw(SDL_Renderer * ctx){
    float x0,y0,x1,y1,x2,y2;
	this->nodes.at(1).get_coords(x0,y0);
	this->nodes.at(2).get_coords(x1,y1);
	this->nodes.at(3).get_coords(x2,y2);
    SDL_FPoint points[4] = {{x0,y0},{x1,y1},{x2,y2},{x0,y0}};
    SDL_RenderDrawLinesF(ctx,points, 4);
}
bool mt_cad::Triangle::hover(int px , int py){
    float x1,y1,x2,y2,x3,y3;
	this->nodes.at(1).get_coords(x1,y1);
	this->nodes.at(2).get_coords(x2,y2);
	this->nodes.at(3).get_coords(x3,y3);
    return this->triPoint(x1,y1,x2,y2,x3,y3,px,py);
}
std::vector<mt_cad::Node> mt_cad::Triangle::get_points(){return this->nodes;}
void mt_cad::Triangle::set_points(std::vector<mt_cad::Node> nodes, bool make_center){
    if (nodes.size()>=this->max_nodes){
        float x0,y0,x1,y1,x2,y2;
        nodes.at(1).get_coords(x0,y0);
        nodes.at(2).get_coords(x1,y1);
        nodes.at(3).get_coords(x2,y2);
        mt_cad::Node central = mt_cad::Node(0,0,XY);
        
        if (make_center){
            central = mt_cad::Node(((x0+x1+x2)/3), ((y0+y1+y2)/3),XY);
        }else{
            central = nodes.at(0);
        }
        
        this->nodes = {central,nodes.at(1),nodes.at(2),nodes.at(3)};
    }else{
        throw std::length_error("Too many nodes for a curve");
    }
}
bool mt_cad::Triangle::triPoint(float x1, float y1, float x2, float y2, float x3, float y3,
              float px, float py) {

  // get the area of the triangle
  float areaOrig = abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));

  // get the area of 3 triangles made between the point
  // and the corners of the triangle
  float area1 = abs((x1 - px) * (y2 - py) - (x2 - px) * (y1 - py));
  float area2 = abs((x2 - px) * (y3 - py) - (x3 - px) * (y2 - py));
  float area3 = abs((x3 - px) * (y1 - py) - (x1 - px) * (y3 - py));

  // if the sum of the three areas equals the original,
  // we're inside the triangle!
  if (area1 + area2 + area3 == areaOrig) {
    return true;
  }
  return false;
}