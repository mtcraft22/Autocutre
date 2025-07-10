#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_atomic.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <GUI/Widget.hpp>


namespace GUI {
	
	class Boton:public GUI::Widget{
		protected:
			
			SDL_Event e;
			int w,h;
			int gapX, gapY;
			
			bool pressed, hover;
			std::string text;
			int x, y;
			
			TTF_Font* font;
			SDL_Color * srccolor;
		public:
			Boton(
				int x,int y,
				int gapX,int gapY, 
				SDL_Color color, 
				SDL_Color colortext,
				std::string text,
				SDL_Event* e,
				TTF_Font * font
			);
			void set_evento(SDL_Event e) override;
			void check_status() override;
			void render(SDL_Renderer* ctx) override;
			void getGap(int& gapX, int& gapY);
			void setGap(int gapX, int gapY);
			
	};
}
