#include <GUI/Boton.hpp>
#include <SDL2/SDL_events.h>
#include <chrono>
#include <cstddef>
#include <iostream>
#include <ostream>
#include <string>
#include <thread>
#define default(x) this->x = x;

GUI::Boton::Boton(int x,int y,int gapX,int gapY, SDL_Color color, SDL_Color colortext,std::string text,SDL_Event* e)
{
	this->text = text;
    this->e = *(e);
	this->x = x;
	this->y = y;
	this->w = 0;
	this->h = 0;
	this->bg = color;
	this->fg = colortext;
	this->gapX = gapX;
	this->gapY = gapY;
	SDL_Rect col = { x,y,10,10 };
	this->box = &col;
    
    this->on_click = NULL;
    this->on_hover = NULL;
    this->on_hover_release = NULL;
}

void GUI::Boton::set_hover_callback(void (*callback )(GUI::Boton * target, void * userdata),void * param){
    this->on_hover = callback;
    this->hoverCallbackUserParams = param;
}

void GUI::Boton::set_hover_release_callback(void (*callback )(GUI::Boton * target, void * userdata),void * param){
    this->on_hover_release = callback;
    this->hoverReleaseCallbackUserParams = param;
}

void GUI::Boton::set_click_callback(void (*callback )(GUI::Boton * target, void * userdata),void * param){
    this->on_click = callback;
    this->clickCallbackUserParams = param;
}
    
    
    bool GUI::Boton::Is_hover(){
        return this->hover;
    }
    
    bool GUI::Boton::Boton::Is_clicked(){
        return this->pressed;
    }
    
    void GUI::Boton::Boton::set_evento(SDL_Event *e){
        this->e = *(e);
        this->check_status();
    }
    
    void GUI::Boton::Boton::check_status(){
     
            
         
            bool prev = this->hover;
            this->hover = false;
            this->pressed = false;
            this->hover = (this->e.motion.x > this->x && this->e.motion.x < this->x + (this->w + (this->gapX*2))) && (this->e.motion.y > this->y && this->e.motion.y < this->y + (this->h + (this->gapY*2)));
          
            
            if (this->e.type == SDL_MOUSEBUTTONDOWN){
                    this->pressed = this->hover && this->e.button.button == SDL_BUTTON_LEFT ;
            }
            if (prev && !hover){
                if(this->on_hover_release != NULL){
                    this->on_hover_release(this,this->hoverReleaseCallbackUserParams);
                }
            }else{

                if(this->hover && !this->pressed){
                    if (this->on_hover != NULL){
                        this->on_hover(this,this->hoverCallbackUserParams);
                    }
                }
            }
            
            if(this->pressed){
                if (this->on_click != NULL){
                    this->on_click(this,this->clickCallbackUserParams);
                }
            }
           
          
        }     
       
        

    void GUI::Boton::Boton::getGap(int* gapX, int* gapY)
    {
        *(gapX) = this->gapX;
        *(gapY) = this->gapY;
    }
        

    void GUI::Boton::Boton::setGap(int gapX, int gapY)
    {
        this->gapX=gapX;
        this->gapY=gapY;
    }
    

    void GUI::Boton::Boton::getPos(int* x, int* y)
    {
        *(x) = this->x;
        *(y) = this->y;
    }
    

    void GUI::Boton::Boton::setPos(int x, int y)
    {
        this->x=x;
        this->y=y;
        this->box->x = x;
        this->box->y = y;
    }
    

    void GUI::Boton::getColor(SDL_Color* color, SDL_Color* colortext)
    {
        *(color) = this->bg;
        *(colortext) = this->fg;
    }
    

    void GUI::Boton::Boton::setColor(SDL_Color color, SDL_Color colortext)
    {
        this->bg =color;
        this->fg = colortext;
    }

   
    

    void GUI::Boton::render(SDL_Renderer* ctx, TTF_Font* font,SDL_Color * srccolor)
    {
        
        SDL_Color bg ={this->bg.r, this->bg.g, this->bg.b, 1};
        SDL_Color fg = {this->fg.r, this->fg.g, this->fg.b, this->fg.a};
        SDL_Surface* txt = TTF_RenderText_Shaded(font, this->text.c_str(), fg, bg);
        SDL_Texture* txt_text = SDL_CreateTextureFromSurface(ctx, txt);
        int w, h;
        SDL_QueryTexture(txt_text, NULL, NULL, &w, &h);
        this->w = w;
        this->h = h;
        SDL_Rect aux = { this->x ,this->y,w + (this->gapX * 2),h + (this->gapY*2) };

        SDL_SetRenderDrawColor(ctx, this->bg.r, this->bg.g, this->bg.b, this->bg.a);
        SDL_RenderFillRect(ctx, &aux);
        SDL_SetRenderDrawColor(ctx, srccolor->r, srccolor->g, srccolor->b, srccolor->a);

        SDL_Rect destTxt = { this->x + (this->gapX / 2),this->y + (this->gapY / 2),w + this->gapX,h + this->gapY };
        SDL_RenderCopy(ctx, txt_text, NULL, &destTxt);
        SDL_FreeSurface(txt);
        SDL_DestroyTexture(txt_text);
    }
    
