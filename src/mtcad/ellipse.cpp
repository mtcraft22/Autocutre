#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "mtcad/Node.hpp"
#include "mtcad/materials.hpp"
#include <mtcad/circle.hpp>
#include <mtcad/ellipse.hpp>
#include <stdexcept>
#include <vector>

const mt_cad::Materials_t mt_cad::Ellipse::material = mt_cad::ELLIPSE;
const int mt_cad::Ellipse::max_nodes = 3;

mt_cad::Ellipse::Ellipse(std::vector<mt_cad::Node> nodes):mt_cad::Circle(nodes){
     if (nodes.size()>=this->max_nodes){
        float x,y;
        nodes.at(0).get_coords(x, y);

        this->nodes = {nodes.at(0),nodes.at(1),nodes.at(2)};
    }else{
        throw std::length_error("Too few nodes for a circle");
    }
};
void mt_cad::Ellipse::draw(SDL_Renderer *ctx)
{
    float x1,y1,x2,y2,x3,y3 = 0;

    this->nodes.at(0).get_coords(x1,y1);
    this->nodes.at(1).get_coords(x2,y2);
    this->nodes.at(2).get_coords(x3,y3);
    this->nodes.at(1).set_canmove(XY);
    this->nodes.at(2).set_canmove(XY);
    this->nodes.at(1).set_coords(x2, y1);
    this->nodes.at(2).set_coords(x1, y3);
    this->nodes.at(1).set_canmove(X);
    this->nodes.at(2).set_canmove(Y);
    int radius = abs(x1 - x2);
    int radius2 = abs(y1 - y3);
    SDL_Point prev = {0,0};
    
    prev.x = cos(0)*radius+x1;
    prev.y = sin(0)*radius2+y1;
    for (int i = 1 ; i<= 360; i+=1){
      
        SDL_RenderDrawLineF(ctx, prev.x, prev.y, cos(((float)i/180)*3.1416)*radius+x1,sin(((float)i/180)*3.1416)*radius2+y1);

        prev.x = cos(((float)i/180)*3.1416)*radius+x1;
        prev.y = sin(((float)i/180)*3.1416)*radius2+y1;
    }
   
}
bool mt_cad::Ellipse::hover(int x , int y){
    float x1,y1,x2,y2,x3,y3 = 0;
    this->nodes.at(0).get_coords(x1,y1);
    this->nodes.at(1).get_coords(x2,y2);
    this->nodes.at(2).get_coords(x3,y3);
    int radius = abs(x1 - x2);
    int radius2 = abs(y1 - y3);
    int distx =  abs(x-x1); int disty =   abs(y-y1) ;
    return distx < radius && disty < radius2;
};