#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_atomic.h>
#include <SDL2/SDL_ttf.h>

#include <string>
#include <GUI/callback.hpp>


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
			callback* on_click = nullptr;
			callback* on_hover_release= nullptr;
			callback* on_hover= nullptr;
			

		
			

		public:
			template<typename C>
			void set_click_callback (Callback<Boton, C> callback){
				callback.set_buton(*(this));
				this->on_click = new Callback(callback);
				
			}
			template<typename H>
			void set_hover_callback (Callback<Boton, H> callback){
				callback.set_buton(*(this));
				this->on_hover =new Callback(callback);
			}
			template<typename Hr>
			void set_hover_release_callback (Callback<Boton, Hr> callback){
				callback.set_buton(*(this));
				this->on_hover_release =new Callback(callback);
			}
			
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
			~Boton(){
				delete on_click;
				delete on_hover;
				delete on_hover_release;
			}
	
			
	};
}
