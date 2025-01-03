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
#pragma once
#include <SDL2/SDL.h>
typedef enum rectitions {XY,X,Y} Restictions ;
namespace mt_cad{
	class Node{
		public:
			Node(float x, float y, Restictions res);
			void draw(SDL_Renderer *ctx);
			void get_coords(float &x, float &y);
			void set_coords(float x,float y);
			Restictions get_canmove();
			void set_canmove(Restictions canmove);
			bool hover(float x, float y);
			void set_angle(float angle);
            float get_angle();
		private:
			Restictions canmove;
			float x,y;
			float angle;
		};
}
