#include <GUI/Boton.hpp>
#include <GUI/callback.hpp>
#include <SDL2/SDL_events.h>
#include <cstddef>
#include <cstdio>
#include <optional>
#include <string>
#include <iostream>


GUI::Boton::Boton(
    int x,int y,
    int gapX,int gapY, 
    SDL_Color color, 
    SDL_Color colortext,
    std::string text,
    SDL_Event* e,
    TTF_Font * font
)
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
	this->box = col;
    this->font = font;
    this->srccolor = &colortext;

}
void GUI::Boton::check_status(){

        
        bool prev = this->hover;
        this->hover = false;
        this->pressed = false;
        this->hover = (this->e.motion.x > this->x && this->e.motion.x < this->x + (this->w + (this->gapX*2))) && (this->e.motion.y > this->y && this->e.motion.y < this->y + (this->h + (this->gapY*2)));
    
    
        if (this->e.type == SDL_MOUSEBUTTONDOWN){
                this->pressed = this->hover && this->e.button.button == SDL_BUTTON_LEFT ;
        }
        if (prev && !hover){
			      auto call = this->get_event(HOVER_RELEASE);
			      if(call){
				        (*call)();
			      }

            
        }else{

            if(this->hover && !this->pressed){
				        auto call = this->get_event(HOVER);
				        if(call){
					          (*call)();
				        }
            }
        }

        if(this->pressed){
			      auto call = this->get_event(CLICK);
			      //std::cout << call << std::endl;
			      if(call){
				        (*call)();
			      }
        }
    
    
    }     

    
void GUI::Boton::set_evento(SDL_Event e) {
	this->e = e;
	this->check_status();
}
void GUI::Boton::Boton::getGap(int& gapX, int& gapY)
{
    gapX = this->gapX;
    gapY = this->gapY;
}

void GUI::Boton::Boton::setGap(int gapX, int gapY)
{
    this->gapX=gapX;
    this->gapY=gapY;
}



void GUI::Boton::render(SDL_Renderer* ctx)
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



