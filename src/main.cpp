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

#include "mtcad/arc.hpp"
#include <GUI/ImageButton.hpp>
#include <GUI/callback.hpp>
#include <GUI/Boton.hpp>

#include <mtcad/mtcad.hpp>

#include <SDL2/SDL.h>

#include <SDL2/SDL_image.h>


#include <cstdlib>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

using namespace std;
int gridsize = 20 ;
const int ticksframe = 1000/60;
int canvas_y_coord = 0;
mt_cad::Materials_t curent_material;
bool creating = false;
bool button_hit = false;
void reset(){
    creating = true;
    button_hit = true;
}
std::vector<GUI::ImageButton *> butons ;
/*void click(GUI::Boton & target,mt_cad::Materials_t& userdata){
    int gapy, gapx;

    target.getGap(gapx, gapy);

    if (gapx == 6 || gapy == 6){
        target.setGap(0, 0);
        creating = false;
        button_hit = false;
    }else{
        for (auto b: butons) {
		    b->setGap(0,0);
        }
        target.setGap(6,6);
        curent_material = userdata;
        reset();
    }

	
}*/
void click(GUI::ImageButton & target,mt_cad::Materials_t& userdata){
    int gapy, gapx;

    target.getGap(gapx, gapy);

    if (gapx == 6 || gapy == 6){
        target.setGap(0, 0);
        creating = false;
        button_hit = false;
    }else{
        for (auto b: butons) {
		    b->setGap(0,0);
        }
        target.setGap(6,6);
        curent_material = userdata;
        reset();
    }

	
}
void render_grid(int sw,int sh,SDL_Texture *  canvas){
        Uint32 * pixels;
        int pitch;
        SDL_LockTexture(canvas, NULL, (void **)&pixels, &pitch);
        for (int y = 0; y<sh; y++){
            for (int x = 0; x<sw; x++) {
        
                if (!(x%gridsize) && !(y%gridsize)){
                   
                    pixels[y*sw+x] = 0xffffff0f;
                }else{
                    pixels[y*sw+x] = 0x0000180f;
                }
                
            }
        }
        SDL_UnlockTexture(canvas);
    }

int main(int argc, char **argv){
    float scale = 1.0;
    int canvas_h = 500*scale; 
    int canvas_w = 500*scale;
    if(SDL_Init(SDL_INIT_EVERYTHING)<0){
        std::cout << SDL_GetError() << std::endl;
        return -1;
    }
    SDL_Window * window = SDL_CreateWindow("Autocutre", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
    SDL_Renderer * ctx = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    int psw , psh;
    int sw,sh;
    SDL_GetWindowSize(window, &sw, &sh);
    canvas_y_coord = sh/4;
    SDL_Texture * canvas = SDL_CreateTexture(ctx, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, sw, sh);
    int ideal = 0;
    for (int i= 0; i <= gridsize;i++){
        if ((canvas_y_coord + i) % gridsize == 0){
            ideal = canvas_y_coord + i;
        }
    }
    SDL_Texture * gui = SDL_CreateTexture(ctx,SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,sw, ideal);
    Uint32 * pixels;
    int pitch;
    std::string path = std::string(SDL_GetBasePath()) + "res/buttons/line.png";
	SDL_Texture* linetext =  IMG_LoadTexture(ctx,path.c_str());
    path = std::string(SDL_GetBasePath()) + "res/buttons/curve.png";
	SDL_Texture* curvetext =  IMG_LoadTexture(ctx,path.c_str());
    path = std::string(SDL_GetBasePath()) + "res/buttons/triangle.png";
	SDL_Texture* triangletext =  IMG_LoadTexture(ctx,path.c_str());
    path = std::string(SDL_GetBasePath()) + "res/buttons/rectangle.png";
	SDL_Texture* rectangletext =  IMG_LoadTexture(ctx,path.c_str());
    path = std::string(SDL_GetBasePath()) + "res/buttons/circle.png";
	SDL_Texture* circletext =  IMG_LoadTexture(ctx,path.c_str());
    path = std::string(SDL_GetBasePath()) + "res/buttons/ellipse.png";
	SDL_Texture* elipsetext =  IMG_LoadTexture(ctx,path.c_str());
    path = std::string(SDL_GetBasePath()) + "res/buttons/quadratic_curve.png";
	SDL_Texture* quadratictext =  IMG_LoadTexture(ctx,path.c_str());
    
    SDL_Color c = {255,255,0,255};
   
    render_grid(sw, sh, canvas);
    
    Uint32 * pixels2;
    int pitch2;

    SDL_LockTexture(gui, NULL, (void **)&pixels2, &pitch2);
    for (int y = 0; y<ideal; y++){
        for (int x = 0; x<sw; x++) {
    
                pixels2[y*sw+x] = 0x0000aa0f;
            
            
        }
    }
    SDL_UnlockTexture(gui);
   
    
 
    
    //mt_cad::Curve Curv = mt_cad::Curve(  nodes  );
    int end,start = SDL_GetTicks(); 
    double delta = 0.0;
    bool run = true;
    bool press = false;
    std::vector<mt_cad::Shape *> shapes;
    mt_cad::Node n = {100,100,XY};
    mt_cad::Node n2 = {200,200,XY};
    mt_cad::Node n3 = {300,300,X};
    mt_cad::Node n4 = {100,200,X};
    shapes.push_back(new mt_cad::Arc({n,n2,n3,n4}));
    

    SDL_Event e;

    bool draggin = false;
    bool innode = false;
    
    int mx,my = 0;

    int sel = 0;
    int selnode = 0;

    GUI::ImageButton linebuton      = GUI::ImageButton(linetext,10,10,c,c,"",&e);
	butons.push_back(&linebuton);
    GUI::ImageButton curvebuton     = GUI::ImageButton(curvetext,60,10,c,c,"",&e);
	butons.push_back(&curvebuton);
    GUI::ImageButton circlebuton    = GUI::ImageButton(circletext,110,10,c,c,"",&e);
	butons.push_back(&circlebuton);
    GUI::ImageButton rectanglebuton = GUI::ImageButton(rectangletext,160,10,c,c,"",&e);
	butons.push_back(&rectanglebuton);
    GUI::ImageButton trianglebuton  = GUI::ImageButton(triangletext,210,10,c,c,"",&e);
	butons.push_back(&trianglebuton);
    GUI::ImageButton ellipsebuton   = GUI::ImageButton(elipsetext,260,10,c,c,"",&e);
	butons.push_back(&ellipsebuton);
    GUI::ImageButton quadraticbuton = GUI::ImageButton(quadratictext,310,10,c,c,"",&e);
	butons.push_back(&quadraticbuton);

  

    mt_cad::Materials_t mat_linebuton = mt_cad::LINE;
    auto call_linebuton = GUI::Callback<GUI::ImageButton, mt_cad::Materials_t> (&mat_linebuton,click);
    linebuton.set_click_callback(call_linebuton);

    mt_cad::Materials_t mat_curvebuton = mt_cad::CURVE;
    auto call_curvebuton = GUI::Callback<GUI::ImageButton, mt_cad::Materials_t> (&mat_curvebuton,click);
    curvebuton.set_click_callback(call_curvebuton);

    mt_cad::Materials_t mat_circlebuton = mt_cad::CIRCLE;
    auto call_circlebuton = GUI::Callback<GUI::ImageButton, mt_cad::Materials_t> (&mat_circlebuton,click);
    circlebuton.set_click_callback(call_circlebuton);

    mt_cad::Materials_t mat_trianglebuton = mt_cad::TRIANGLE;
    auto call_trianglebuton = GUI::Callback<GUI::ImageButton, mt_cad::Materials_t> (&mat_trianglebuton,click);
    trianglebuton.set_click_callback(call_trianglebuton);

    mt_cad::Materials_t mat_ellipsebuton = mt_cad::ELLIPSE;
    auto call_ellipsebuton = GUI::Callback<GUI::ImageButton, mt_cad::Materials_t> (&mat_ellipsebuton,click);
    ellipsebuton.set_click_callback(call_ellipsebuton);

    mt_cad::Materials_t mat_quadraticbuton = mt_cad::QUADRATIC;
    auto call_quadraticbuton = GUI::Callback<GUI::ImageButton, mt_cad::Materials_t> (&mat_quadraticbuton,click);
    quadraticbuton.set_click_callback(call_quadraticbuton);

    mt_cad::Materials_t mat_rectanglebuton = mt_cad::RECTANGLE;
    auto call_rectanglebuton = GUI::Callback<GUI::ImageButton, mt_cad::Materials_t> (&mat_rectanglebuton,click);
    rectanglebuton.set_click_callback(call_rectanglebuton);


    std::vector<mt_cad::Node> nodes_new_shape;
    int offx , offy;
	while (run) {
        
        start = SDL_GetTicks();
        delta = start-end;
        if ( delta > ticksframe){
            end = start;
            
            SDL_SetRenderDrawColor(ctx, 55, 55, 55,255);
            SDL_RenderClear(ctx);
            SDL_SetRenderDrawColor(ctx,255, 255, 255, 255);
            psw = sw;
            psh = sh;
            SDL_GetWindowSize(window, &sw, &sh);
            
            SDL_Rect  dest = {gridsize*(offx/gridsize),gridsize*(offy/gridsize),sw,sh};
            SDL_RenderCopy(ctx, canvas, NULL, &dest);

           
            
            if (shapes.size() > 0){
                for ( int i = 0; i < shapes.size(); i++ ){
                    shapes.at(i)->draw(ctx);
                }
            }
            
            if (sel >= 0 && shapes.size()> 0){
                for (int i = 0; i< shapes.at(sel)->get_points().size(); i++){
                SDL_SetRenderDrawColor(ctx, 255, 0, 0,255);
                shapes.at(sel)->get_points().at(i).draw(ctx);
                if(draggin && shapes.at(sel)->get_points().at(i).hover(mx, my) ){
                    
                    shapes.at(sel)->get_points().at(i).set_coords(gridsize*(mx/gridsize), gridsize*(my/gridsize));
                }
                SDL_SetRenderDrawColor(ctx,255, 255, 255, 255);
                }
                SDL_SetRenderDrawColor(ctx,255, 0, 0, 255);
            }
           
           
            //Curv.draw(ctx);
            
            while (SDL_PollEvent(&e)) {
                linebuton.set_evento(&e);
                curvebuton.set_evento(&e);
                circlebuton.set_evento(&e);
                trianglebuton.set_evento(&e);
                rectanglebuton.set_evento(&e);
                ellipsebuton.set_evento(&e);
                quadraticbuton.set_evento(&e);
                if (e.type == SDL_QUIT) {
                    run = false;
                }
                if (e.type == SDL_WINDOWEVENT){
                    if (e.window.event == SDL_WINDOWEVENT_RESIZED){
                        
                        psw = sw;
                        psh = sh;
                        int pideal = ideal;
                        SDL_GetWindowSize(window, &sw, &sh);
                        SDL_DestroyTexture(canvas);
                        canvas = SDL_CreateTexture(ctx, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, sw, sh);

                        render_grid(sw, sh, canvas);
                        canvas_y_coord = sh/4;
                        for (int i= 0; i <= gridsize;i++){
                            if ((canvas_y_coord + i) % gridsize == 0){
                                ideal = canvas_y_coord + i;
                            }
                        }
                        if (shapes.size() > 0){
                            for ( int i = 0; i < shapes.size(); i++ ){
                                for (int i2 = 0; i2< shapes.at(i)->get_points().size(); i2++){
                                    std::vector<mt_cad::Node> nodes = shapes.at(i)->get_points();
                                    float x,y ;
                                    Restictions res =  nodes.at(i2).get_canmove();
                                    nodes.at(i2).set_canmove(XY);
                                    nodes.at(i2).get_coords(x, y);
                                    
                                    nodes.at(i2).set_coords(x,y + (ideal-pideal));
                                    nodes.at(i2).set_canmove(res);
                                    shapes.at(i)->set_points( nodes,true);
                                }
                            }
                        }
                        
                       
                    }
                    
                }
                if (e.type == SDL_KEYDOWN){
                    std::vector<mt_cad::Node> nodes = {};
                    if (shapes.size()>0){
                        std::vector<mt_cad::Node> nodes = shapes.at(sel)->get_points();
                    }
                    switch (e.key.keysym.sym ) {
                        case SDLK_LEFT:
                            
                            
                            if (shapes.size()>0){
                                sel  ++;
                                if (sel > (shapes.size() -1)){sel = 0 ;}
                            }
                            break;
                        case SDLK_RIGHT:
                           
                            if (shapes.size()>0){
                                sel --;
                                if (sel < 0){sel = shapes.size()-1 ;}
                            }
                            break;
                        case SDLK_ESCAPE :
                            for (auto b: butons) {
                                b->setGap(0,0);
                            }
                            creating = false;
                            button_hit  = false;
                            break;
                        case SDLK_DELETE:
                            if (sel >= 0 && shapes.size() >= 0){
                                delete shapes.at(sel);
                                shapes.erase(shapes.begin() + sel);
                                sel = -1;
                            
                            }
                            break;
                        case SDLK_e:
                            if (mt_cad::Circle * c = dynamic_cast<mt_cad::Circle*>(shapes.at(sel))){
                                    break;
                                }
                            if (shapes.size()>=0 && sel > -1){
                                for (int i = 1 ; i< shapes.at(sel)->get_points().size(); i++){
                                    float px,py;
                                    float cx,cy;
                                    nodes.at(0).get_coords(cx, cy);
                                    nodes.at(i).get_coords(px, py);
                                    
                                    double radius = sqrtf (abs(abs(px - cx) * abs(px - cx)) + (abs(py - cy) * abs(py - cy)));
                                    float dy = py - cy;
                                    float dx = px - cx;
                                    double theta = atan2(dy,dx);
                                    theta *= 180/3.1416;
                                    if (theta < 0) theta = 360 + theta;
                                    nodes.at(i).set_angle(theta+ 1);
                                    px = cos(((double)(nodes.at(i).get_angle())/180)*3.1416)*radius+cx;
                                    py = sin(((double)(nodes.at(i).get_angle())/180)*3.1416)*radius+cy;
                                    nodes.at(i).set_coords(px, py);
                                    
                                } 
                                shapes.at(sel)->set_points(nodes,true);
                            }
                            break;
                        case SDLK_q:
                            
                            if (shapes.size()>=0 && sel > -1){
                                for (int i = 1 ; i< shapes.at(sel)->get_points().size(); i++){
                                    if (mt_cad::Circle * c = dynamic_cast<mt_cad::Circle*>(shapes.at(sel))){
                                        break;
                                    }
                                    float px,py;
                                    float cx,cy;
                                    nodes.at(0).get_coords(cx, cy);
                                    nodes.at(i).get_coords(px, py);
                                    
                                    double radius = sqrtf ((abs(px - cx) * abs(px - cx)) + (abs(py - cy) * abs(py - cy)));
                                    float dy = py - cy;
                                    float dx = px - cx;
                                    double theta = atan2(dy,dx);
                                    theta *= 180/3.1416;
                                    if (theta < 0){theta = 360 + theta;};
                        
                                    nodes.at(i).set_angle(theta- 1);
                                    px = cos(((double)(nodes.at(i).get_angle())/180)*3.1416)*radius+cx;
                                    py = sin(((double)(nodes.at(i).get_angle())/180)*3.1416)*radius+cy;
                                    
                                    nodes.at(i).set_coords(px, py);
                                    
                                }
                                shapes.at(sel)->set_points(nodes,true);}
                                break;
                            
                    }
                    
                    
                }
                if (e.type == SDL_MOUSEWHEEL){
                   // int pmx = mx ;
                    //int pmy = my ;
                    if (e.wheel.y > 0){
                        scale *= 1.5;
                        
                    
                    }
                    if (e.wheel.y < 0){
                        scale *= 0.5;
                        
                        
                    }
                    
                  
                    
                }
                if(e.type == SDL_MOUSEBUTTONDOWN){
                  
                    press = true;
                    if (creating){
                        
                        
                        switch (curent_material) {
                      
                            case mt_cad::LINE:
                                
                                if (nodes_new_shape.size() < mt_cad::Line::max_nodes){
                                    if(!button_hit){
                                        
                                        nodes_new_shape.push_back({(float)mx,(float)my,XY});
                                    }
                                    button_hit = false;
                                   
                                }
                                if(nodes_new_shape.size() >= mt_cad::Line::max_nodes) {
                                    mt_cad::Line * line = new mt_cad::Line(nodes_new_shape);
                                    shapes.push_back(line);
                                    creating = false;
                                    nodes_new_shape.clear();
									for (auto b: butons) {
										b->setGap(0,0);
									}
                                }
                                break;
                            case mt_cad::CURVE:
                                if (nodes_new_shape.size() < mt_cad::Curve::max_nodes){
                                    if(!button_hit){
                                        
                                        nodes_new_shape.push_back({(float)mx,(float)my,XY});
                                    }
                                    button_hit = false;
                                   
                                }
                                if(nodes_new_shape.size() >= mt_cad::Curve::max_nodes) {
                                    mt_cad::Curve * curve = new mt_cad::Curve(nodes_new_shape);
                                    shapes.push_back(curve);
                                    creating = false;
                                    nodes_new_shape.clear();
									for (auto b: butons) {
										b->setGap(0,0);
									}
                                }
                                break;
                            case mt_cad::QUADRATIC:
                                if (nodes_new_shape.size() < mt_cad::Quadratic_curve::max_nodes){
                                    if(!button_hit){
                                        
                                        nodes_new_shape.push_back({(float)mx,(float)my,XY});
                                    }
                                    button_hit = false;
                                   
                                }
                                if(nodes_new_shape.size() >= mt_cad::Quadratic_curve::max_nodes) {
                                    mt_cad::Quadratic_curve * Quadratic_curve = new mt_cad::Quadratic_curve(nodes_new_shape);
                                    shapes.push_back(Quadratic_curve);
                                    creating = false;
                                    nodes_new_shape.clear();
									for (auto b: butons) {
										b->setGap(0,0);
									}
                                }
                                break;
                            case mt_cad::CIRCLE:
                                if (nodes_new_shape.size() < mt_cad::Circle::max_nodes){
                                    if(!button_hit){
                                        
                                        nodes_new_shape.push_back({(float)mx,(float)my,XY});
                                    }
                                    button_hit = false;
                                   
                                }
                                if(nodes_new_shape.size() >= mt_cad::Circle::max_nodes) {
                                    mt_cad::Circle * Circle = new mt_cad::Circle(nodes_new_shape);
                                    shapes.push_back(Circle);
                                    creating = false;
                                    nodes_new_shape.clear();
									for (auto b: butons) {
										b->setGap(0,0);
									}
                                }
                                break;
                            case mt_cad::TRIANGLE:
                                if (nodes_new_shape.size() < mt_cad::Triangle::max_nodes){
                                    if(!button_hit){
                                        
                                        nodes_new_shape.push_back({(float)mx,(float)my,XY});
                                    }
                                    button_hit = false;
                                   
                                }
                                if(nodes_new_shape.size() >= mt_cad::Triangle::max_nodes) {
                                    mt_cad::Triangle * Triangle = new mt_cad::Triangle(nodes_new_shape);
                                    shapes.push_back(Triangle);
                                    creating = false;
                                    nodes_new_shape.clear();
									for (auto b: butons) {
										b->setGap(0,0);
									}
                                }
                                
                                break;
                            case mt_cad::RECTANGLE:
                                if (nodes_new_shape.size() < mt_cad::Rectangle::max_nodes){
                                    if(!button_hit){
                                        
                                        nodes_new_shape.push_back({(float)mx,(float)my,XY});
                                    }
                                    button_hit = false;
                                   
                                }
                                if(nodes_new_shape.size() >= mt_cad::Rectangle::max_nodes) {
                                    mt_cad::Rectangle * Rectangle = new mt_cad::Rectangle(nodes_new_shape);
                                    shapes.push_back(Rectangle);
                                    creating = false;
                                    nodes_new_shape.clear();
									for (auto b: butons) {
										b->setGap(0,0);
									}
                                }
                                break;
                            case mt_cad::ELLIPSE:
                                if (nodes_new_shape.size() < mt_cad::Ellipse::max_nodes){
                                    if(!button_hit){
                                        
                                        nodes_new_shape.push_back({(float)mx,(float)my,XY});
                                    }
                                    button_hit = false;
                                   
                                }
                                if(nodes_new_shape.size() >= mt_cad::Ellipse::max_nodes) {
                                    mt_cad::Ellipse * Ellipse = new mt_cad::Ellipse(nodes_new_shape);
                                    shapes.push_back(Ellipse);
                                    creating = false;
                                    nodes_new_shape.clear();
									for (auto b: butons) {
										b->setGap(0,0);
									}
                                }
                                break;
                            case mt_cad::ARC:
                              break;
                            }
                    }
                    if(!draggin){
                        bool des = false;
                        if (sel >= 0 && shapes.size()){
                            for (mt_cad::Node n : shapes.at(sel)->get_points()){
                                
                                if (n.hover(mx, my)){
                                    des = true;
                                    
                                }
                            }
                            if (!des){
                                sel = -1;
                                innode = false;
                            }
                        }
                        std::vector<int> hover_shapes;
                        if (shapes.size()> 0 && shapes.size()){
                            for ( int x = 0; x < shapes.size(); x++ ){
                                if (shapes.at(x)->hover(mx, my)){
                                    hover_shapes.push_back(x);
                                    sel = x;

                                }
                            }
                            mt_cad::Node central = shapes.at(0)->get_points()[0];
                            float cx,cy;
                            central.get_coords(cx, cy);
                            float distmin = (abs(cx-mx)  *  abs(cx-mx)) + (abs(cy-my)  *  abs(cy-my));
                            for (int h : hover_shapes){
                                for (auto central : shapes.at(h)->get_points()) {
                                    float dist;
                            
                                    float cx,cy;
                                    central.get_coords(cx, cy);

                                    dist = sqrt((abs(cx-mx)  *  abs(cx-mx)) + (abs(cy-my)  *  abs(cy-my)));
                                    if (dist < distmin){
                                        distmin = dist;
                                        sel = h;
                                    }
                                }
                                

                            }
                        }
                      
                        
                        
                        cout << "selected: " << sel << endl;
                    }
                  
                }
                if(e.type == SDL_MOUSEBUTTONUP){
                    press = false;
                    draggin = false;
                    innode = false;
                     
                }
                if(e.type == SDL_MOUSEMOTION){
                    if(press){  draggin = true;press = false;}
                
                    mx = e.motion.x;
                    my = e.motion.y;
                    
                    if (draggin ){
                        if (sel < 0 && shapes.size()){
                        
                           offy += e.motion.yrel;
                           offx += e.motion.xrel;
                            if(draggin){
                                for ( int i = 0; i < shapes.size(); i++ ){
                                    vector<mt_cad::Node> points;

                                    for (mt_cad::Node n :shapes.at(i)->get_points()){
                                        float x,y;
                                        n.get_coords(x, y);
                                        points.push_back({x+e.motion.xrel,y+e.motion.yrel,n.get_canmove()});
                                    } 
                                    shapes.at(i)->set_points(points, false);
                                }
                            }
                  
                        }
                        if (!innode && sel >= 0 && shapes.size()){
                            for (int i = 0; i< shapes.at(sel)->get_points().size(); i++){
                                if(draggin && shapes.at(sel)->get_points().at(i).hover(mx, my) ){
                                    std::vector<mt_cad::Node> nodes = shapes.at(sel)->get_points();
                                    nodes.at(i).set_coords(gridsize * (std::trunc(mx/gridsize)),(gridsize * (std::trunc(my/gridsize))));
                                    shapes.at(sel)->set_points( nodes, true);
                                    selnode = i;
                                    innode = true;
                                    if (i == 0){
                                        for (int i = 1; i< shapes.at(sel)->get_points().size(); i++){
                                            std::vector<mt_cad::Node> nodes = shapes.at(sel)->get_points();
                                            float x,y ;
                                            nodes.at(i).get_coords(x, y);
                                            
                                            nodes.at(i).set_coords(x + e.motion.xrel,y + e.motion.yrel);
                                            shapes.at(sel)->set_points( nodes, true);
                                            
                                        }
                                    }
                                    if (mt_cad::Arc * c = dynamic_cast<mt_cad::Arc*>(shapes.at(sel))){
                                        if (i == 3){
                                           
                                            std::vector<mt_cad::Node> nodes = shapes.at(sel)->get_points();
                                            float x,y ;
                                            nodes.at(3).get_coords(x, y);
                                            nodes.at(3).set_coords(x + e.motion.xrel,y + e.motion.yrel);
                                            shapes.at(sel)->set_points( nodes,true);
                                            
                                        }
                                    }
                                    break;
                            }
                        }
                        }else if (draggin && sel >= 0 && shapes.size()> 0) {
                            std::vector<mt_cad::Node> nodes = shapes.at(sel)->get_points();
                            nodes.at(selnode).set_coords(gridsize * (std::trunc(mx/gridsize)),(gridsize * (std::trunc(my/gridsize))));

                            shapes.at(sel)->set_points( nodes,true);

                            if (mt_cad::Arc * c = dynamic_cast<mt_cad::Arc*>(shapes.at(sel))){
                                if (selnode == 3){
                                   
                                    std::vector<mt_cad::Node> nodes = shapes.at(sel)->get_points();
                                    float x,y ;
                                    nodes.at(3).get_coords(x, y);
                                    nodes.at(3).set_coords(x + e.motion.xrel,y + e.motion.yrel);
                                    shapes.at(sel)->set_points( nodes,true);
                                    
                                }
                            }
                            if (selnode == 0){
                                for (int i = 1; i< shapes.at(sel)->get_points().size(); i++){
                                    std::vector<mt_cad::Node> nodes = shapes.at(sel)->get_points();
                                    float x,y ;
                                    nodes.at(i).get_coords(x, y);
                                    nodes.at(i).set_coords(x + e.motion.xrel,y + e.motion.yrel);
                                    shapes.at(sel)->set_points( nodes,true);
                                }
                            }
                        }
                        
                      
                    
                    }
                }

            } 
            SDL_DestroyTexture(gui);
            gui = SDL_CreateTexture(ctx, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, sw, ideal);

            
            SDL_Rect  dest2 = {0,0,sw,ideal};

            SDL_LockTexture(gui, NULL, (void **)&pixels2, &pitch2);
            for (int y = 0; y<ideal; y++){
                for (int x = 0; x<sw; x++) {
            
                        pixels2[y*sw+x] = 0x0000aa0f;
                    
                    
                }
            }
            SDL_UnlockTexture(gui);
            SDL_RenderCopy(ctx, gui, NULL, &dest2);
            linebuton.render(ctx);
            curvebuton.render(ctx);
            circlebuton.render(ctx);
            trianglebuton.render(ctx);
            rectanglebuton.render(ctx);
            ellipsebuton.render(ctx);
            quadraticbuton.render(ctx);
            SDL_RenderPresent(ctx);
            
            
        }else{
            SDL_Delay(ticksframe -delta);
        }

    }
    SDL_DestroyTexture(canvas);
    SDL_DestroyTexture(gui);
    SDL_DestroyTexture(linetext);
    SDL_DestroyTexture(curvetext);
    SDL_DestroyTexture(circletext);
    SDL_DestroyTexture(rectangletext);
    SDL_DestroyTexture(triangletext);
    SDL_DestroyTexture(elipsetext);
    SDL_DestroyTexture(quadratictext);
    SDL_DestroyRenderer(ctx);
    for (auto &s  : shapes){
        delete s;
    }
    shapes.clear();
    SDL_Quit();
    return 0;
}
