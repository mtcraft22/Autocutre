#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_ttf.h>
#include <atomic>
#include <mutex>
#include <string>
#include <thread>
namespace GUI {
	
	class Boton{
		protected:
			
			SDL_Event e;
			int w,h;
			int gapX, gapY;
			SDL_Rect* box;
			SDL_Color color;
			SDL_Color colortext;
			bool pressed, hover;
			std::string text;
			int x, y;
			void check_status();
			void * hoverCallbackUserParams;
			void * clickCallbackUserParams;
			void * hoverReleaseCallbackUserParams;

			void (*on_hover)(GUI::Boton * target, void *userdata);
			void (*on_click)(GUI::Boton * target, void *userdata);
			void (*on_hover_release)(GUI::Boton * target, void *userdata);
			
		public:
			void set_hover_callback(void (*callback )(GUI::Boton * target, void * userdata),void * param);
			void set_hover_release_callback(void (*callback )(GUI::Boton * target, void *userdata),void *param);
			void set_click_callback(void (*callback )(GUI::Boton * target, void *userdata),void *param);
			
			Boton(int x,int y,int gapX,int gapY, SDL_Color color, SDL_Color colortext,std::string text,SDL_Event* e);
			void set_evento(SDL_Event* e);
			void getGap(int* gapX, int* gapY);
			void setGap(int gapX, int gapY);
			void getPos(int* x, int* y);
			void setPos(int x, int y);
			void getColor(SDL_Color* color, SDL_Color* colortext);
			void setColor(SDL_Color color, SDL_Color colortext);
			void render(SDL_Renderer* ctx, TTF_Font* font, SDL_Color* srccolor);
			bool Is_clicked();
			bool Is_hover();
			
	};
}
