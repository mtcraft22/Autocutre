#include "GUI/Boton.hpp"
#include "GUI/Widget.hpp"
#include <GUI/ImageButton.hpp>
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <iostream>
#include <ostream>

GUI::ImageButton::ImageButton(
		SDL_Texture *img, 
		int x, int y, 
		SDL_Color bg, 
		SDL_Color fg,
		SDL_Event *e,
		int gapy , 
		int gapx 
	):GUI::Boton(x,y,gapx,gapy,bg,fg,"",e,NULL),img(img) 
	{
		SDL_QueryTexture(img,nullptr,nullptr,&this->box.w,&this->box.h);

	}

void GUI::ImageButton::render(SDL_Renderer * ctx){
	 GUI::Widget::render(ctx);
	int w, h;
 	this->x = this->box.x;
	this->y = this->box.y; 
	SDL_QueryTexture(this->img, NULL, NULL, &w, &h);

	SDL_Rect aux = { this->x ,this->y,w + (this->gapX ),h + (this->gapY) };

	SDL_SetRenderDrawColor(ctx, this->bg.r, this->bg.g, this->bg.b, this->bg.a);
	SDL_RenderFillRect(ctx, &aux);

	//SDL_SetRenderDrawColor(ctx, this->fg.r, this->fg.g, this->fg.b, this->bg.a);

	SDL_Rect destTxt = { this->x + (this->gapX / 2),this->y + (this->gapY / 2),w ,h  };
	SDL_RenderCopy(ctx, this->img, NULL, &destTxt);
}
