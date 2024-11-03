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
#include "mtcad/Node.hpp"
#include "mtcad/Rectangle.hpp"
#include "mtcad/Shape.hpp"
#include "mtcad/Triangle.hpp"
#include "mtcad/circle.hpp"
#include "mtcad/curve.hpp"
#include "mtcad/ellipse.hpp"
#include "mtcad/line.hpp"
#include "mtcad/materials.hpp"
#include "mtcad/quadratic_curve.hpp"
#include <GUI/Boton.hpp>
#include <SDL2/SDL_keycode.h>
#include <map>
#include <mtcad/mtcad.hpp>

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_filesystem.h>
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>

#include <GUI/ImageButton.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <cstdlib>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

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
void click(GUI::Boton * target,void * userdata){
    int gapy, gapx;

    target->getGap(&gapx, &gapy);

    if (gapx == 6 || gapy == 6){
        target->setGap(0, 0);
        creating = false;
        button_hit = false;
    }else{
        for (auto b: butons) {
		    b->setGap(0,0);
        }
        target->setGap(6,6);
        curent_material = *(mt_cad::Materials_t *) userdata;
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
    
    if(SDL_Init(SDL_INIT_EVERYTHING)<0){
        std::cout << SDL_GetError() << std::endl;
        return -1;
    }
    SDL_Window * window = SDL_CreateWindow("curbas", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1080, 720, SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
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
    std::cout << path << std::endl;



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
   
    
    std::vector<mt_cad::Node> nodes5 = {{500,500+ideal,XY},{540,500+ideal,XY},{500,540+ideal,XY}};
    mt_cad::Ellipse *tri5 = new mt_cad::Ellipse(  nodes5  );
    
    //mt_cad::Curve Curv = mt_cad::Curve(  nodes  );
    int end,start = SDL_GetTicks(); 
    double delta = 0.0;
    bool run = true;

    std::vector<mt_cad::Shape *> shapes;

    shapes.push_back(tri5);

    

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

    mt_cad::Materials_t mat = mt_cad::LINE;
    linebuton.set_click_callback(click, &mat);
    mt_cad::Materials_t mat2 = mt_cad::CURVE;
    curvebuton.set_click_callback(click, &mat2);
    mt_cad::Materials_t mat3 = mt_cad::CIRCLE;
    circlebuton.set_click_callback(click, &mat3);
    mt_cad::Materials_t mat4 = mt_cad::RECTANGLE;
    rectanglebuton.set_click_callback(click, &mat4);
    mt_cad::Materials_t mat5 = mt_cad::TRIANGLE;
    trianglebuton.set_click_callback(click, &mat5);
    mt_cad::Materials_t mat6 = mt_cad::ELLIPSE;
    ellipsebuton.set_click_callback(click, &mat6);
    mt_cad::Materials_t mat7 = mt_cad::QUADRATIC;
    quadraticbuton.set_click_callback(click, &mat7);
    std::vector<mt_cad::Node> nodes_new_shape;
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
            
            SDL_Rect  dest = {0,0,sw,sh};
            SDL_RenderCopy(ctx, canvas, NULL, &dest);

           
            
    
            for ( int i = 0; i < shapes.size(); i++ ){
                
                shapes.at(i)->draw(ctx);
            }
            for (int i = 0; i< shapes.at(sel)->get_points().size(); i++){
                SDL_SetRenderDrawColor(ctx, 255, 0, 0,255);
                shapes.at(sel)->get_points().at(i).draw(ctx);
                if(draggin && shapes.at(sel)->get_points().at(i).hover(mx, my) ){
                    
                    shapes.at(sel)->get_points().at(i).set_coords(gridsize*(mx/gridsize), gridsize*(my/gridsize));
                }
                SDL_SetRenderDrawColor(ctx,255, 255, 255, 255);
            }
            SDL_SetRenderDrawColor(ctx,255, 0, 0, 255);
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
                        for ( int i = 0; i < shapes.size(); i++ ){
                           for (int i2 = 0; i2< shapes.at(i)->get_points().size(); i2++){
                                    std::vector<mt_cad::Node> nodes = shapes.at(i)->get_points();
                                    int x,y ;
                                    Restictions res =  nodes.at(i2).get_canmove();
                                    nodes.at(i2).set_canmove(XY);
                                    nodes.at(i2).get_coords(x, y);
                                    
                                    nodes.at(i2).set_coords(x,y + (ideal-pideal));
                                    nodes.at(i2).set_canmove(res);
                                    shapes.at(i)->set_points( nodes);
                                }
                            }
                        
                       
                    }
                    
                }
                if (e.type == SDL_KEYDOWN){
                    if (e.key.keysym.sym == SDLK_ESCAPE){
                        for (auto b: butons) {
                            b->setGap(0,0);
                        }
                        creating = false;
                        button_hit  = false;
                    }
                }
                if(e.type == SDL_MOUSEBUTTONDOWN){
                    if (creating){
                        
                        
                        switch (curent_material) {
                      
                            case mt_cad::LINE:
                                
                                if (nodes_new_shape.size() < mt_cad::Line::max_nodes){
                                    if(!button_hit){
                                        std::cout << mx << " " << my << std::endl;
                                        nodes_new_shape.push_back({mx,my,XY});
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
                                        std::cout << mx << " " << my << std::endl;
                                        nodes_new_shape.push_back({mx,my,XY});
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
                                        std::cout << mx << " " << my << std::endl;
                                        nodes_new_shape.push_back({mx,my,XY});
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
                                        std::cout << mx << " " << my << std::endl;
                                        nodes_new_shape.push_back({mx,my,XY});
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
                                        std::cout << mx << " " << my << std::endl;
                                        nodes_new_shape.push_back({mx,my,XY});
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
                                        std::cout << mx << " " << my << std::endl;
                                        nodes_new_shape.push_back({mx,my,XY});
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
                                        std::cout << mx << " " << my << std::endl;
                                        nodes_new_shape.push_back({mx,my,XY});
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
                        }
                        
                    }
                    if(!draggin){
                        std::vector<int> hover_shapes;
                        for ( int x = 0; x < shapes.size(); x++ ){
                            if (shapes.at(x)->hover(mx, my)){
                                hover_shapes.push_back(x);
                                sel = x;

                            }
                        }
                        mt_cad::Node central = shapes.at(0)->get_points()[0];
                        int cx,cy;
                        central.get_coords(cx, cy);
                        float distmin = (abs(cx-mx)  *  abs(cx-mx)) + (abs(cy-my)  *  abs(cy-my));
                        for (int h : hover_shapes){
                            for (auto central : shapes.at(h)->get_points()) {
                                float dist;
                          
                                int cx,cy;
                                central.get_coords(cx, cy);

                                dist = sqrt((abs(cx-mx)  *  abs(cx-mx)) + (abs(cy-my)  *  abs(cy-my)));
                                if (dist < distmin){
                                    distmin = dist;
                                    sel = h;
                                }
                            }
                            

                        }
                        
                        
                    }
                    draggin = true;
                }
                if(e.type == SDL_MOUSEBUTTONUP){
                    draggin = false;
                    innode = false;
                     
                }
                if(e.type == SDL_MOUSEMOTION){
                 
                    mx = e.motion.x;
                    my = e.motion.y;
                    
                    if (draggin ){
                        if (!innode){
                            for (int i = 0; i< shapes.at(sel)->get_points().size(); i++){
                                if(draggin && shapes.at(sel)->get_points().at(i).hover(mx, my) ){
                                    std::vector<mt_cad::Node> nodes = shapes.at(sel)->get_points();
                                    nodes.at(i).set_coords(gridsize * (std::trunc(mx/gridsize)),(gridsize * (std::trunc(my/gridsize))));
                                    shapes.at(sel)->set_points( nodes);
                                    selnode = i;
                                    innode = true;
                                    if (i == 0){
                                        for (int i = 1; i< shapes.at(sel)->get_points().size(); i++){
                                            std::vector<mt_cad::Node> nodes = shapes.at(sel)->get_points();
                                            int x,y ;
                                            nodes.at(i).get_coords(x, y);
                                            
                                            nodes.at(i).set_coords(x + e.motion.xrel,y + e.motion.yrel);
                                            shapes.at(sel)->set_points( nodes);
                                            
                                        }
                                    }
                                    break;
                            }
                        }
                        }else if (draggin) {
                            std::vector<mt_cad::Node> nodes = shapes.at(sel)->get_points();
                            nodes.at(selnode).set_coords(gridsize * (std::trunc(mx/gridsize)),(gridsize * (std::trunc(my/gridsize))));

                            shapes.at(sel)->set_points( nodes);
                                if (selnode == 0){
                                    for (int i = 1; i< shapes.at(sel)->get_points().size(); i++){
                                        std::vector<mt_cad::Node> nodes = shapes.at(sel)->get_points();
                                        int x,y ;
                                        nodes.at(i).get_coords(x, y);
                                        nodes.at(i).set_coords(x + e.motion.xrel,y + e.motion.yrel);
                                        shapes.at(sel)->set_points( nodes);
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