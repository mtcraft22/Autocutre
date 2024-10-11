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
#include <mtcad/Shape.hpp>
#include <Bezier.hpp>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_stdinc.h>


App::Bezier::Bezier(SDL_app app){
    this->application = app;
}
int App::Bezier::get_ideal_y_canvas_cord(){
    this->ideal = 0;
    for (int i= 0; i <= gridsize;i++){
        if ((canvas_y_coord + i) % gridsize == 0){
            this->ideal = canvas_y_coord + i;
        }
    }
    return this->ideal;
}
void App::Bezier::render_gui(){
    int sw,sh;
    this->application.get_windowSize(sw, sh);
    this->canvas_y_coord = sh/4;
    this->get_ideal_y_canvas_cord();
    SDL_DestroyTexture(this->gui);
    this->gui = SDL_CreateTexture(this->application.get_ctx(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, sw, this->ideal);
    SDL_Rect  dest2 = {0,0,sw,this->ideal};
    int *pixels;
    int pitch;
    SDL_LockTexture(gui, NULL, (void **)&pixels, &pitch);
    for (int y = 0; y<ideal; y++){
        for (int x = 0; x<sw; x++) {
    
                pixels[y*sw+x] = 0x0000330f;
            
            
        }
    }
    SDL_UnlockTexture(gui);
    SDL_RenderCopy(this->application.get_ctx(), gui, NULL, &dest2);

}
void App::Bezier::render_grid(){
        int sw,sh;
        this->application.get_windowSize(sw, sh);
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
        SDL_RenderCopy(this->application.get_ctx(), gui, NULL, NULL);

}
App::Bezier::~Bezier(){
    SDL_DestroyTexture(this->canvas);
    SDL_DestroyTexture(this->gui);
    for ( auto &shape : this->shapes){
        delete shape;
    }
    this->shapes.clear();
}
std::vector<mt_cad::Shape *> App::Bezier::get_shapes() { return this->shapes; }
std::vector<GUI::ImageButton> App::Bezier::get_shape_creation_buttons() { return shape_creation_buttons; }
SDL_Texture* App::Bezier::get_gui() { return gui; }
SDL_Texture* App::Bezier::get_canvas() { return canvas; }
int App::Bezier::get_drawing_state() { return drawing_state; }
int App::Bezier::get_sel() { return sel; }
int App::Bezier::get_gridsize() { return gridsize; }
SDL_Renderer * App::Bezier::get_ctx(){
    return this->application.get_ctx();
}

void App::Bezier::set_shapes(std::vector<mt_cad::Shape *> shapes) {
 this->shapes = shapes; 
}
void App::Bezier::set_shape_creation_buttons(std::vector<GUI::ImageButton> shape_creation_buttons) {
 this->shape_creation_buttons = shape_creation_buttons; 
}
void App::Bezier::set_gui(SDL_Texture* gui) {
 this->gui = gui; 
}
void App::Bezier::set_canvas(SDL_Texture* canvas) {
 this->canvas = canvas; 
}
void App::Bezier::set_drawing_state(int drawing_state) {
 this->drawing_state = drawing_state; 
}
void App::Bezier::set_sel(int sel) {
 this->sel = sel; 
}
void App::Bezier::set_gridsize(int gridsize) {
 this->gridsize = gridsize; 
}



