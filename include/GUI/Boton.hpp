#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <optional>
#include <string>
#include <GUI/callback.hpp>
#include <vector>

namespace GUI {
	
	class Boton{
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
			bool Is_clicked();
			bool Is_hover();
			
		private:
			Callback<class W, class T> click = Callback<class W, class T>();
			Callback<class W, class T> _hover = Callback<class W, class T>();
			Callback<class W, class T> hover_release = Callback<class W, class T>();
		public:
			template <typename c, typename W>
			void set_click_callback (Callback<W,c>& callback);
			template <typename H, typename W>
			void set_hover_callback (Callback< W,H>& callback);
			template <typename Hr, typename W>
			void set_hover_release_callback (Callback< W,Hr>& callback);
			
			Boton(
				int x,int y,
				int gapX,int gapY, 
				SDL_Color color, 
				SDL_Color colortext,
				std::string text,
				SDL_Event* e
			);
			
			void set_evento(SDL_Event* e);
			void getGap(int& gapX, int& gapY);
			void setGap(int gapX, int gapY);
			void getPos(int& x, int& y);
			void setPos(int x, int y);
			void getColor(SDL_Color& color, SDL_Color& colortext);
			void setColor(SDL_Color color, SDL_Color colortext);
			void render(SDL_Renderer* ctx, TTF_Font* font, SDL_Color* srccolor);
	
			
	};
}
