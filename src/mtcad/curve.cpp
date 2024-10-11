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
#include <cmath>
#include <mtcad/curve.hpp>
#include <mtcad/Node.hpp>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <stdexcept>
#include <vector>

mt_cad::Curve::Curve(std::vector<mt_cad::Node> points  ){

    if (points.size()>=this->max_nodes){
        int x0,y0,x1,y1,x2,y2;
        points.at(0).get_coords(x0,y0);
        points.at(1).get_coords(x1,y1);
        points.at(2).get_coords(x2,y2);
        mt_cad::Node central = mt_cad::Node(x0,y0-20 ,XY);
        this->nodes = {central,points.at(0),points.at(1),points.at(2)};
    }else{
        throw std::length_error("Too many nodes for a curve");
    }
}
std::vector<mt_cad::Node> mt_cad::Curve::get_points(){
    return this->nodes;
}
void mt_cad::Curve::set_points(std::vector<mt_cad::Node> nodes){
    if (nodes.size()>=this->max_nodes){
        int x0,y0,x1,y1,x2,y2;
        nodes.at(1).get_coords(x0,y0);
        nodes.at(2).get_coords(x1,y1);
        nodes.at(3).get_coords(x2,y2);
        mt_cad::Node central = mt_cad::Node(x0,y0-20 ,XY);
        this->nodes = {central,nodes.at(1),nodes.at(2),nodes.at(3)};
    }else{
        throw std::length_error("Too many nodes for a curve");
    }
}
void mt_cad::Curve::draw (SDL_Renderer * ctx){
	int x0,y0,x1,y1,x2,y2;
	this->nodes.at(1).get_coords(x0,y0);
	this->nodes.at(2).get_coords(x1,y1);
	this->nodes.at(3).get_coords(x2,y2);
    float px = ((1-0)*(1-0))*x0 + 2*(1-0)*0*x1 + (0*0)*x2;
    float py = ((1-0)*(1-0))*y0 + 2*(1-0)*0*y1 + (0*0)*y2;
    for (float i = 0; i < 1.1; i+=0.1){
        float x = ((1-i)*(1-i))*x0 + 2*(1-i)*i*x1 + (i*i)*x2;
        float y = ((1-i)*(1-i))*y0 + 2*(1-i)*i*y1 + (i*i)*y2;
        SDL_RenderDrawLineF(ctx, px, py, x, y);
        px = x;
        py = y;

    }
}
bool mt_cad::Curve::triPoint(float x1, float y1, float x2, float y2, float x3, float y3,float px, float py) {

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
bool mt_cad::Curve::hover(int x, int y){
	int x0,y0,x1,y1,x2,y2;
	this->nodes.at(1).get_coords(x0,y0);
	this->nodes.at(2).get_coords(x1,y1);
	this->nodes.at(3).get_coords(x2,y2);
  
    return triPoint(x0, y0, x1, y1, x2, y2, x, y);
}