#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_atomic.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <GUI/Widget.hpp>


namespace GUI {
	
	class Boton:public Widget{
		protected:
			
			SDL_Event e;
			int w,h;
			int gapX, gapY;
			SDL_Rect* box;
			SDL_Color bg;
			SDL_Color fg;
			bool pressed, hover;
			std::string text;
			int x, y;
			void check_status();
		
			

		
			

		public:
			
			
			Boton(
				int x,int y,
				int gapX,int gapY, 
				SDL_Color color, 
				SDL_Color colortext,
				std::string text,
				SDL_Event* e
			);
			

			void getGap(int& gapX, int& gapY);
			void setGap(int gapX, int gapY);
			void getPos(int& x, int& y);
			void setPos(int x, int y);
			void getColor(SDL_Color& color, SDL_Color& colortext);
			void setColor(SDL_Color color, SDL_Color colortext);
	};
}
