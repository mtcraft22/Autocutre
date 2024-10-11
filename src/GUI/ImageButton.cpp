#include <GUI/ImageButton.hpp>
#include <SDL2/SDL.h>
#include <iostream>
#include <ostream>
GUI::ImageButton::ImageButton(SDL_Texture *img, int x, int y, SDL_Color color, SDL_Color colortext, std::string text,
	SDL_Event *e):GUI::Boton(x,y,0,0,color,colortext,"",e),img(img) {

		SDL_QueryTexture(img,NULL,NULL,&this->w,&this->h);
        this->gapX = this->gapY = 0;
}
void GUI::ImageButton::render(SDL_Renderer * ctx){
    int w,h;
    SDL_QueryTexture(this->img,NULL, NULL, &w, &h);
    SDL_Rect dest = {this->x,this->y,w,h};
    SDL_RenderCopy(ctx, this->img,NULL, &dest);
}