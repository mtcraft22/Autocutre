#include "mtcad/materials.hpp"
#include <mtcad/quadratic_curve.hpp>
const int mt_cad::Quadratic_curve::max_nodes = 4;
const mt_cad::Materials_t mt_cad::Quadratic_curve::material = QUADRATIC;
void mt_cad::Quadratic_curve::draw(SDL_Renderer* ctx){
    int x0,y0,x1,y1,x2,y2,x3,y3;
    this->nodes.at(1).get_coords(x0,y0);
    this->nodes.at(2).get_coords(x1,y1);
    this->nodes.at(3).get_coords(x2,y2);
    this->nodes.at(4).get_coords(x3,y3);
    float px = ((1-0)*(1-0)*(1-0))*x0 + 3*((1-0)*(1-0))*0*x1 +3*(1-0)*(0*0)*x2 +  (0*0*0)*x3;
    float py = ((1-0)*(1-0)*(1-0))*y0 + 3*((1-0)*(1-0))*0*y1 +3*(1-0)*(0*0)*y2 +  (0*0*0)*y3;
    for (float i = 0; i < 1.0001; i+=0.0001){
        float x = ((1-i)*(1-i)*(1-i))*x0 + 3*((1-i)*(1-i))*i*x1 +3*(1-i)*(i*i)*x2 +  (i*i*i)*x3;
        float y = ((1-i)*(1-i)*(1-i))*y0 + 3*((1-i)*(1-i))*i*y1 +3*(1-i)*(i*i)*y2 +  (i*i*i)*y3;
        SDL_RenderDrawLineF(ctx, px, py, x, y);
        px = x;
        py = y;
    } 
}